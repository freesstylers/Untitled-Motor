/*
  -----------------------------------------------------------------------------
  This source file is part of OGRE
  (Object-oriented Graphics Rendering Engine)
  For the latest info, see http://www.ogre3d.org/

  Copyright (c) 2000-2014 Torus Knot Software Ltd

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  -----------------------------------------------------------------------------
*/
#include "OgreGpuProgram.h"
#include "OgreHighLevelGpuProgramManager.h"
#include "OgreLogManager.h"
#include "OgreRoot.h"
#include "OgreStringConverter.h"

#include "OgreGLSLShader.h"
#include "OgreGLSLShader.h"

#include "OgreGLSLPreprocessor.h"
#include "OgreGLSLProgramManager.h"
#include "OgreGLUtil.h"
#include "OgreGLUniformCache.h"

namespace Ogre {
    /// Get OpenGL GLSL shader type from OGRE GPU program type.
    static GLenum getGLShaderType(GpuProgramType programType)
    {
        switch (programType)
        {
        case GPT_VERTEX_PROGRAM:
            return GL_VERTEX_SHADER;
        case GPT_HULL_PROGRAM:
            return GL_TESS_CONTROL_SHADER;
        case GPT_DOMAIN_PROGRAM:
            return GL_TESS_EVALUATION_SHADER;
        case GPT_GEOMETRY_PROGRAM:
            return GL_GEOMETRY_SHADER;
        case GPT_FRAGMENT_PROGRAM:
            return GL_FRAGMENT_SHADER;
        case GPT_COMPUTE_PROGRAM:
            return GL_COMPUTE_SHADER;
        }

        return 0;
    }

    GLSLShader::GLSLShader(
        ResourceManager* creator,
        const String& name, ResourceHandle handle,
        const String& group, bool isManual, ManualResourceLoader* loader)
        : GLSLShaderCommon(creator, name, handle, group, isManual, loader)
        , mGLShaderHandle(0)
        , mGLProgramHandle(0)
    {
        if (createParamDictionary("GLSLShader"))
        {
            setupBaseParamDictionary();
            ParamDictionary* dict = getParamDictionary();

            dict->addParameter(ParameterDef(
                "attach",
                "name of another GLSL program needed by this program",
                PT_STRING), &msCmdAttach);
            dict->addParameter(ParameterDef(
                "column_major_matrices",
                "Whether matrix packing in column-major order.",
                PT_BOOL), &msCmdColumnMajorMatrices);
        }

        mType = GPT_VERTEX_PROGRAM; // default value, to be corrected after the constructor with GpuProgram::setType()
        mSyntaxCode = "glsl" + StringConverter::toString(Root::getSingleton().getRenderSystem()->getNativeShadingLanguageVersion());
        
        // There is nothing to load
        mLoadFromFile = false;
    }

    GLSLShader::~GLSLShader()
    {
        // Have to call this here rather than in Resource destructor
        // since calling virtual methods in base destructors causes crash
        if (isLoaded())
        {
            unload();
        }
        else
        {
            unloadHighLevel();
        }
    }

    void GLSLShader::submitSource()
    {
        if (mSource.empty())
            return;

        const RenderSystemCapabilities* rsc = Root::getSingleton().getRenderSystem()->getCapabilities();

        bool clipDistBug =
            ((OGRE_PLATFORM == OGRE_PLATFORM_WIN32) || (OGRE_PLATFORM == OGRE_PLATFORM_WINRT)) &&
            rsc->getVendor() == GPU_INTEL;

        size_t versionPos = mSource.find("#version");
        int shaderVersion = 100;
        size_t belowVersionPos = 0;

        if(versionPos != String::npos)
        {
            shaderVersion = StringConverter::parseInt(mSource.substr(versionPos+9, 3));
            belowVersionPos = mSource.find('\n', versionPos) + 1;
        }

        // OSX driver only supports glsl150+ in core profile
        bool shouldUpgradeToVersion150 = !rsc->isShaderProfileSupported("glsl130") && shaderVersion < 150;

        // Add standard shader input and output blocks, if missing.
        // Assume blocks are missing if gl_Position is missing.
        if (rsc->hasCapability(RSC_GLSL_SSO_REDECLARE) && (mSource.find("vec4 gl_Position") == String::npos))
        {
            size_t mainPos = mSource.find("void main");
            // Only add blocks if shader is not a child
            // shader, i.e. has a main function.
            if (mainPos != String::npos)
            {
                String clipDistDecl = clipDistBug ? "float gl_ClipDistance[1];" : "float gl_ClipDistance[];";
                String inBlock = "in gl_PerVertex\n{\nvec4 gl_Position;\nfloat gl_PointSize;\n"+clipDistDecl+"\n} gl_in[];\n\n";
                String outBlock = "out gl_PerVertex\n{\nvec4 gl_Position;\nfloat gl_PointSize;\n"+clipDistDecl+"\n};\n\n";

                if (shaderVersion >= 150 || shouldUpgradeToVersion150)
                {
                    switch (mType)
                    {
                    case GPT_VERTEX_PROGRAM:
                        mSource.insert(belowVersionPos, outBlock);
                        break;
                    case GPT_GEOMETRY_PROGRAM:
                        mSource.insert(belowVersionPos, outBlock);
                        mSource.insert(belowVersionPos, inBlock);
                        break;
                    case GPT_DOMAIN_PROGRAM:
                        mSource.insert(belowVersionPos, outBlock);
                        mSource.insert(belowVersionPos, inBlock);
                        break;
                    case GPT_HULL_PROGRAM:
                        mSource.insert(belowVersionPos, outBlock.substr(0, outBlock.size() - 3) + " gl_out[];\n\n");
                        mSource.insert(belowVersionPos, inBlock);
                        break;
                    case GPT_FRAGMENT_PROGRAM:
                    case GPT_COMPUTE_PROGRAM:
                        // Fragment and compute shaders do
                        // not have standard blocks.
                        break;
                    }
                }
                else if(mType == GPT_VERTEX_PROGRAM && shaderVersion >= 130) // shaderVersion < 150, means we only have vertex shaders
                {
                	// TODO: can we have SSO with GLSL < 130?
                    mSource.insert(belowVersionPos, "out vec4 gl_Position;\nout float gl_PointSize;\nout "+clipDistDecl+"\n\n");
                }
            }
        }

        if(shouldUpgradeToVersion150)
        {
            if(belowVersionPos != 0)
                mSource = mSource.erase(0, belowVersionPos); // drop old definition

            // automatically upgrade to glsl150. thank you apple.
            const char* prefixFp =
                    "#version 150\n"
                    "#define varying in\n"
                    "#define texture1D texture\n"
                    "#define texture2D texture\n"
                    "#define texture3D texture\n"
                    "#define textureCube texture\n"
                    "#define texture2DLod textureLod\n"
                    "#define textureCubeLod textureLod\n"
                    "#define shadow2DProj textureProj\n"
                    "#define gl_FragColor FragColor\n"
                    "out vec4 FragColor;\n";
            const char* prefixVp =
                    "#version 150\n"
                    "#define attribute in\n"
                    "#define varying out\n";

            mSource.insert(0, mType == GPT_FRAGMENT_PROGRAM ? prefixFp : prefixVp);
        }

        // Submit shader source.
        const char *source = mSource.c_str();
        OGRE_CHECK_GL_ERROR(glShaderSource(mGLShaderHandle, 1, &source, NULL));
    }

    bool GLSLShader::compile(bool checkErrors)
    {
        // Create shader object.
        GLenum GLShaderType = getGLShaderType(mType);
        OGRE_CHECK_GL_ERROR(mGLShaderHandle = glCreateShader(GLShaderType));

        //TODO GL 4.3 KHR_debug

        // if (getGLSupport()->checkExtension("GL_KHR_debug") || gl3wIsSupported(4, 3))
        //     glObjectLabel(GL_SHADER, mGLShaderHandle, 0, mName.c_str());

        // if (Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(RSC_SEPARATE_SHADER_OBJECTS))
        // {
        //     OGRE_CHECK_GL_ERROR(mGLProgramHandle = glCreateProgram());
        //     if(getGLSupport()->checkExtension("GL_KHR_debug") || gl3wIsSupported(4, 3))
        //         glObjectLabel(GL_PROGRAM, mGLProgramHandle, 0, mName.c_str());
        // }

        submitSource();

        OGRE_CHECK_GL_ERROR(glCompileShader(mGLShaderHandle));

        // Check for compile errors
        int compiled = 0;
        OGRE_CHECK_GL_ERROR(glGetShaderiv(mGLShaderHandle, GL_COMPILE_STATUS, &compiled));

        if(!checkErrors)
            return compiled == 1;

        String compileInfo = getObjectInfo(mGLShaderHandle);

        if (!compiled)
            OGRE_EXCEPT(Exception::ERR_RENDERINGAPI_ERROR, getResourceLogName() + " " + compileInfo, "compile");

        // probably we have warnings
        if (!compileInfo.empty())
            LogManager::getSingleton().stream(LML_WARNING) << getResourceLogName() << " " << compileInfo;

        return compiled == 1;
    }

    void GLSLShader::unloadHighLevelImpl(void)
    {
        OGRE_CHECK_GL_ERROR(glDeleteShader(mGLShaderHandle));

        if (Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(RSC_SEPARATE_SHADER_OBJECTS) && mGLProgramHandle)
        {
            OGRE_CHECK_GL_ERROR(glDeleteProgram(mGLProgramHandle));
        }

        // destroy all programs using this shader
        GLSLProgramManager::getSingletonPtr()->destroyAllByShader(this);

        mGLShaderHandle = 0;
        mGLProgramHandle = 0;
        mLinked = 0;
    }

    void GLSLShader::buildConstantDefinitions() const
    {
        // We need an accurate list of all the uniforms in the shader, but we
        // can't get at them until we link all the shaders into a program object.

        // Therefore instead parse the source code manually and extract the uniforms.
        createParameterMappingStructures(true);
        GLSLProgramManager::getSingleton().extractUniformsFromGLSL(mSource, *mConstantDefs, mName);


        // Also parse any attached sources.
        for (GLSLProgramContainer::const_iterator i = mAttachedGLSLPrograms.begin();
             i != mAttachedGLSLPrograms.end(); ++i)
        {
            GLSLShaderCommon* childShader = *i;

            GLSLProgramManager::getSingleton().extractUniformsFromGLSL(
                childShader->getSource(), *mConstantDefs, childShader->getName());
        }
    }

    void GLSLShader::attachToProgramObject(const GLuint programObject)
    {
        // attach child objects
        for (auto childShader : mAttachedGLSLPrograms)
        {
            childShader->attachToProgramObject(programObject);
        }
        OGRE_CHECK_GL_ERROR(glAttachShader(programObject, mGLShaderHandle));
    }


    void GLSLShader::detachFromProgramObject(const GLuint programObject)
    {
        OGRE_CHECK_GL_ERROR(glDetachShader(programObject, mGLShaderHandle));
        logObjectInfo( "Error detaching " + mName + " shader object from GLSL Program Object", programObject);
        // attach child objects
        GLSLProgramContainerIterator childprogramcurrent = mAttachedGLSLPrograms.begin();
        GLSLProgramContainerIterator childprogramend = mAttachedGLSLPrograms.end();

        while (childprogramcurrent != childprogramend)
        {
            GLSLShaderCommon* childShader = *childprogramcurrent;
            childShader->detachFromProgramObject(programObject);
            ++childprogramcurrent;
        }
    }


    const String& GLSLShader::getLanguage(void) const
    {
        static const String language = "glsl";

        return language;
    }

    GLuint GLSLShader::getGLProgramHandle() {
        //TODO This should be removed and the compile() function
        // should use glCreateShaderProgramv
        // for separable programs which includes creating a program.
        if (mGLProgramHandle == 0)
        {
            OGRE_CHECK_GL_ERROR(mGLProgramHandle = glCreateProgram());
            if (mGLProgramHandle == 0)
            {
                //TODO error handling
            }
        }
        return mGLProgramHandle;
    }
}

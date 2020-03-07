#pragma once

#include <OgreFileSystemLayer.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreRTShaderSystem.h>

class ResourceManager	//carga de recursos (por ahora)
{
public:
	ResourceManager(const Ogre::String& path);
	~ResourceManager();

	void setup();

	void addSceneManager(Ogre::SceneManager* sm);

private:

	void locateOgreResources();
	void loadOgreResources();

	bool initRTShaderSystem();
	void wipeRTShaderSystem();

	Ogre::FileSystemLayer* FSLayer;
	Ogre::String path;
	Ogre::String RTShaderLibPath;


	Ogre::RTShader::ShaderGenerator* shaderGenerator;
	OgreBites::SGTechniqueResolverListener* materialMgrListener;
};


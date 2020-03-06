// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Entity.h"


#include <OgreRoot.h>
#include <OgreException.h>
#include <OgreConfigFile.h>
#include <OgreViewport.h>
#include <iostream>
#include <OgreRenderSystem.h>
#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <OgreGpuProgramManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreRTShaderSystem.h>
#include <OgreSGTechniqueResolverListener.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>

//#include <iostream>
//#include <btBulletDynamicsCommon.h>
//#include <OgreSceneManager.h>
//#include <OgreConfigFile.h>
//#include <OgreTextureManager.h>
//#include <OgreResource.h>
//#include <OgreResourceManager.h>
//#include <OgreGpuProgramManager.h>


#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include "windows.h"
#include <fmod.hpp>

using namespace FMOD;

Ogre::Camera* cam;
Ogre::Root* root;

Ogre::FileSystemLayer* FSLayer;
Ogre::RTShader::ShaderGenerator* ShaderGenerator; // The Shader generator instance.
OgreBites::SGTechniqueResolverListener* MaterialMgrListener;
Ogre::ConfigOptionMap opt;
Ogre::RenderWindow* mWindow;
Ogre::RenderSystem* rs;

void SetupWindow() {

	//		WINDOW		//

	rs = root->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	root->setRenderSystem(rs);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "ERROR: Couldn't initialize SDL.",
			"BaseApplication::setup");
	}

	opt = rs->getConfigOptions();

	mWindow = root->initialise(true, "Motor Casa Paco");
}


void SetupResources()
{
	using namespace Ogre;


	FSLayer = new Ogre::FileSystemLayer("./");

	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		ShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		// Create and register the material manager listener if it doesn't exist yet.
		if (!MaterialMgrListener)
		{
			MaterialMgrListener = new OgreBites::SGTechniqueResolverListener(ShaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(MaterialMgrListener);
		}
	}

	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = FSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath("./assets/ogre"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/Shaders/programs/HLSL", type, sec);
	}

	std::string shaderPath = arch + "/Shaders/programs/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(shaderPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(shaderPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(shaderPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(shaderPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(shaderPath + "/HLSL", type, sec);
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

#ifdef  _DEBUG
    int main(int argc, char* argv[])
#else
    #include <Windows.h>
    int WINAPI
    WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	//Initialise OGRE

	Ogre::String pluginPath;

#ifdef  _DEBUG
		pluginPath = "plugins_d.cfg";
#else
		pluginPath = "plugins.cfg";
#endif

	root = new Ogre::Root(pluginPath);

//	FSLayer = new Ogre::FileSystemLayer("Motor Casa Paco");

	SetupWindow();

	SetupResources();


	


	Ogre::SceneManager* mSM = root->createSceneManager();

	// create the camera
	cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(100000000);
	cam->setAutoAspectRatio(true);

	Ogre::SceneNode* mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->translate(100, 100, 100);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = mWindow->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::Entity* ogreEntity = mSM->createEntity("sphere.mesh");
	ogreEntity->setMaterialName("testSphere/sphereTest");


	Ogre::SceneNode* Node = mSM->getRootSceneNode()->createChildSceneNode("test1");
	Node->attachObject(ogreEntity);
	Node->translate(10, 1, 10);
	Node->scale(0.1, 0.1, 0.1);

	Ogre::Entity* ogreEntity2 = mSM->createEntity("sphere.mesh");
	ogreEntity2->setMaterialName("testSphere/sphereTest");


	Ogre::SceneNode* Node2 = mSM->getRootSceneNode()->createChildSceneNode("test2");
	Node2->attachObject(ogreEntity2);
	Node2->translate(0, 10, 0);
	Node2->scale(0.1, 0.1, 0.1);

	Ogre::Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);



	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			continue;
		}

		if (!root->renderOneFrame())
			break;
	}

	// clean up
	delete root;
	SDL_Quit();

    return 0;
}
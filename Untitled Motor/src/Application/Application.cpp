// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Entity.h"


#include <OgreRoot.h>
#include <SDL.h>
#include "windows.h"
#include <iostream>
#include <fmod.hpp>
#include <btBulletDynamicsCommon.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreResource.h>
#include <OgreResourceManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreGpuProgramManager.h>
#include <OgreRTShaderSystem.h>


using namespace FMOD;

Ogre::Camera* cam;
Ogre::Root* root;

Ogre::FileSystemLayer* FSLayer;
Ogre::RTShader::ShaderGenerator* ShaderGenerator; // The Shader generator instance.


void SetupResources()
{
	using namespace Ogre;

	// Load resource paths from config file
	ConfigFile cf;
	cf.load("resources.cfg");

	// Go through all sections & settings in the file
	ConfigFile::SectionIterator itSection = cf.getSectionIterator();

	String strGroupName, strLocation, strType;
	while (itSection.hasMoreElements())
	{
		// Resource group.  "General", etc
		strGroupName = itSection.peekNextKey();

		ConfigFile::SettingsMultiMap* mapSettings = itSection.getNext();
		ConfigFile::SettingsMultiMap::iterator itSetting = mapSettings->begin();

		for (; itSetting != mapSettings->end(); ++itSetting)
		{
			// Zip or FileSystem
			strType = itSetting->first;
			// Filepath
			strLocation = itSetting->second;
			ResourceGroupManager::getSingleton().addResourceLocation(strLocation, strType, strGroupName);
		}
	}
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
	// Initialise OGRE
		Ogre::String pluginPath;
#ifdef  _DEBUG
		pluginPath = "plugins_d.cfg";
#else
		pluginPath = "plugins.cfg";
#endif

	FSLayer = new Ogre::FileSystemLayer("Motor Casa Paco");

	root = new Ogre::Root(pluginPath, FSLayer->getWritablePath("ogre.cfg"), FSLayer->getWritablePath("ogre.log"));


	Ogre::RenderSystem* rs = root->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	root->setRenderSystem(rs);


	Ogre::String mSolutionPath;
	mSolutionPath = "./assets";

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mSolutionPath, "FileSystem", "General");
	
	Ogre::RenderWindow* mWindow = root->initialise(true, "Motor Casa Paco");

	SetupResources();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);


	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		ShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		// Core shader libs not found -> shader generating will fail.
		// Create and register the material manager listener if it doesn't exist yet.
	}


	Ogre::SceneManager* mSM = root->createSceneManager();
	Ogre::Camera* mCamera=mSM->createCamera("MainCam");
	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::Entity* ogreEntity = mSM->createEntity("sphere.mesh");
	
	
	Ogre::SceneNode* Node = mSM->getRootSceneNode()->createChildSceneNode();
	Node->attachObject(ogreEntity);




	//root->startRendering();

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
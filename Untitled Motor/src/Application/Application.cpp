// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Entity.h"

#include <stdio.h>
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_syswm.h>
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

using namespace FMOD;

Ogre::Camera* cam;
Ogre::Root* root;

#ifdef  _DEBUG
    int main(int argc, char* argv[])
#else
    #include <Windows.h>
    int WINAPI
    WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// Initialise OGRE

#ifdef  _DEBUG
    root = new Ogre::Root("plugins_d.cfg");
#else
    root = new Ogre::Root("plugins.cfg");
#endif

	Ogre::RenderSystem* rs = root->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	root->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	root->setRenderSystem(rs);

	Ogre::ConfigFile cf;
	Ogre::String name, locType;
	cf.load("resources.cfg");
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
	Ogre::RenderWindow* mWindow = root->initialise(true, "Motor Casa Paco");

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();  

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

	//Ogre::Entity* ogreEntity = mSM->createEntity("sinbad.mesh");

	/*
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
					"BaseApplication::setup");
		SDL_Quit();
		return 1;
	}

	root->setRenderSystem(*(root->getAvailableRenderers().begin()));

	root->restoreConfig();
	root->initialise(false);

	Ogre::NameValuePairList params; // ogre window / render system params
	*/
	//Ogre::RenderWindow* ogreWindow = root->createRenderWindow("myWindowTitle", 800, 600, false, &params);

	// create OGRE scene manager, camera, viewports, etc

	// FMOD TESTING
	FMOD::System* system;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system); // Creamos el objeto system
	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	result = system->init(128, FMOD_INIT_NORMAL, 0); // Inicializacion de FMOD

	FMOD::Sound* sound;
	result = system->createSound(
		"assets/sound/startup.mp3", // path al archivo de sonido
		FMOD_DEFAULT, // valores (por defecto en este caso: sin loop, 2D)
		0, // informacion adicional (nada en este caso)
		&sound);

	FMOD::Channel* channel;
	result = system->playSound(
		sound, // buffer que se "engancha" a ese canal
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		false, // arranca sin "pause" (se reproduce directamente)
		&channel); // devuelve el canal que asigna
		// el sonido ya se esta reproduciendo

		///-----initialization_start-----

	// BULLET PHYSICS TESTING
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	/*
	SDL_Window* sdlWindow = SDL_CreateWindow("myWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	if (sdlWindow == nullptr) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't create SDL Window" + *SDL_GetError(),
			"BaseApplication::setup");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"SDL_CreateRenderer Error: " + *SDL_GetError(),
			"BaseApplication::setup");
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return 1;
	}

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
		SDL_DestroyWindow(sdlWindow);
		SDL_Quit();
		return 1;
	}

	// grab a string representing the NSWindow pointer
	Ogre::String winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.win.window);

	// assign the NSWindow pointer to the parentWindowHandle parameter
	params.insert(std::make_pair("externalWindowHandle", winHandle));
	*/
	//COSAS


	//cam->setPosition(0, 0, 80);
	//cam->lookAt(0, 0, -300);
	//cam->setNearClipDistance(5);
	//

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
	//SDL_DestroyRenderer(renderer);
	//SDL_DestroyWindow(sdlWindow);
	SDL_Quit();

    return 0;
}
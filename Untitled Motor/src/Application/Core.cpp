#include "Core.h"


#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreBitesConfigDialog.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreWindowEventUtilities.h>

Core::Core(const Ogre::String& appName) : appName(appName)
{
	resourceManager = new ResourceManager("./assets");
	inputManager = new InputManager();
	root = nullptr;
}

Core::~Core()
{
	delete resourceManager;
	delete inputManager;
}

void Core::init()
{
	setupRoot();

	if (checkConfig()) {
		setup();
	}
}

void Core::initTestScene()
{

	// create the camera

	Ogre::Camera* cam = sm->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(100000000);
	cam->setAutoAspectRatio(true);

	Ogre::SceneNode* mCamNode = sm->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->translate(100, 100, 100);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = window->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::Entity* ogreEntity = sm->createEntity("barrel.mesh");
	ogreEntity->setMaterialName("test");


	Ogre::SceneNode* Node = sm->getRootSceneNode()->createChildSceneNode("test1");
	Node->attachObject(ogreEntity);
	Node->translate(10, 1, 10);
	//Node->scale(0.1, 0.1, 0.1);

	Ogre::Entity* ogreEntity2 = sm->createEntity("sphere.mesh");
	ogreEntity2->setMaterialName("sphereTest");


	Ogre::SceneNode* Node2 = sm->getRootSceneNode()->createChildSceneNode("test2");
	Node2->attachObject(ogreEntity2);
	Node2->translate(0, 10, 0);
	Node2->scale(0.1, 0.1, 0.1);

	Ogre::Light* luz = sm->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = sm->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
}

void Core::start()
{
	root->startRendering();
}

void Core::pollEvents()
{
	if (sdlWindow == nullptr)
		return;  // SDL events not initialized

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			root->queueEndRendering();
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(sdlWindow)) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = window;
					//win->resize(event.window.data1, event.window.data2);
					win->windowMovedOrResized();
					windowResized(win);
				}
			}
			break;
		default:
			//llamar a InputManager
			inputManager->InputManagement(event);	//Se podría ir a pincho de forma mas especifica llamando directamente al de boton, tecla, etc
			break;
		}
	}

	// just avoid "window not responding"
	Ogre::WindowEventUtilities::messagePump();
}

bool Core::checkConfig()
{
	if (!root->restoreConfig())
	{
		return root->showConfigDialog(OgreBites::getNativeConfigDialog());
	}
	else return true;
}

void Core::setupRoot()
{
	//Initialise OGRE

	Ogre::String pluginPath;

	#ifdef  _DEBUG
		pluginPath = "plugins_d.cfg";
		root = new Ogre::Root("plugins_d.cfg", "window_d.cfg");
	#else
	pluginPath = "plugins.cfg";
		root = new Ogre::Root("plugins.cfg", "window.cfg");
	#endif

	if (!Ogre::FileSystemLayer::fileExists(pluginPath))
	{	// IG2: OGRE_CONFIG_DIR tiene un valor absoluto no portable
		//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "IG2ApplicationContext::createRoot");
	}


	if (!(root->restoreConfig() || root->showConfigDialog(nullptr)))
		return;
}

void Core::setup()
{
	root->initialise(false);
	setupWindow(appName);

	resourceManager->setup();
	inputManager->setup();

	sm = root->createSceneManager();

	resourceManager->addSceneManager(sm);

	root->addFrameListener(this);
}

void Core::shutdown()
{

	if (window != nullptr)
	{
		root->destroyRenderTarget(window);
		window = nullptr;
	}

	if (sdlWindow != nullptr)
	{
		SDL_DestroyWindow(sdlWindow);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		sdlWindow = nullptr;
	}
}


void Core::setupWindow(Ogre::String windowName)
{
	uint32_t w, h;

	Ogre::ConfigOptionMap ropts = root->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w;
	mode >> token;
	mode >> h;

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	Ogre::NameValuePairList params;

	params["FSAA"] = ropts["FSAA"].currentValue;
	params["vsync"] = ropts["VSync"].currentValue;
	params["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	window = root->createRenderWindow(windowName, w, h, false, &params);


//////////por si queremos que la ventana oculte el cursor
	SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
	SDL_ShowCursor(true);

/*
	Ogre::RenderSystem* rs = root->getRenderSystemByName("Direct3D11 Rendering Subsystem");
	root->setRenderSystem(rs);


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "ERROR: Couldn't initialize SDL.",
			"BaseApplication::setup");
	}

	Ogre::ConfigOptionMap opt = rs->getConfigOptions();

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}
*/
}


Ogre::Root* Core::getRoot()
{
	return root;
}

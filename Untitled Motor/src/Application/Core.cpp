#include "Core.h"


#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreBitesConfigDialog.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <stdexcept>


#include "ResourceManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include <iostream>

#include "TestComponent.h"
#include "EventManager.h"

Core::Core(const Ogre::String& appName) : appName(appName)
{
	
	audioManager = new AudioManager();
	root = nullptr;
}

Core::~Core()
{
	ResourceManager::clean();
	InputManager::clean();
	PhysicsManager::clean();
	SceneManager::clean();
}

Core* Core::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool Core::setupInstance(const Ogre::String& appName)
{
	if (instance == 0)
	{
		instance = new Core(appName);
		return true;
	}

	return false;
}

void Core::clean()
{
	delete instance;
}

void Core::init()
{
	try { ResourceManager::setupInstance("./assets/"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try { SceneManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try	{ InputManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("InputManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try	{ PhysicsManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("PhysicsManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	setupRoot();

	if (checkConfig()) {
		setup();
	}
}

void Core::changeScene(Ogre::String name)
{
	SceneManager::getInstance()->changeScene(name);
}

void Core::initPhysicsTestScene()
{

	//Aki para que suene temporalmente
	audioManager->playMusic("assets/sound/rock.wav",0);
	audioManager->playSound("assets/sound/a.wav",1);
	audioManager->setVolume(.2, 0);

	Ogre::Camera* cam = sm->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(100000000);
	cam->setAutoAspectRatio(true);

	Ogre::SceneNode* mCamNode = sm->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->translate(100, 50, 200);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = window->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	std::string cubeid = "cubo";
	Ogre::SceneNode* cubeNode = sm->getRootSceneNode()->createChildSceneNode(cubeid);
	Ogre::Entity* cubeEntity = sm->createEntity("cube.mesh");
	cubeEntity->setMaterialName("test");
	cubeNode->attachObject(cubeEntity);
	cubeNode->translate(Ogre::Vector3(0, 50, 0));
	cubeNode->showBoundingBox(true);

	//se le pasa una referencia al nodo al que esta ligado
	PhysicsManager::getInstance()->addBox(cubeid, btVector3(cubeNode->getPosition().x, cubeNode->getPosition().y, cubeNode->getPosition().z), btVector3(70, 70, 70), 10)->setUserPointer(cubeNode);

	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);
	std::string planeid = "plano";
	Ogre::SceneNode* planeNode = sm->getRootSceneNode()->createChildSceneNode(planeid);
	Ogre::Entity* plane = sm->createEntity("mPlane1080x800");
	plane->setMaterialName("test");
	planeNode->attachObject(plane);
	planeNode->translate(0, -100, 0);

	//se le pasa una referencia al nodo al que esta ligado
	PhysicsManager::getInstance()->addBox(planeid, btVector3(planeNode->getPosition().x, planeNode->getPosition().y, planeNode->getPosition().z), btVector3(1080, 0, 800), 0)->setUserPointer(planeNode);


	Ogre::Light* luz = sm->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = sm->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
}

void Core::testMessageSystem() {
	// Normal check
	TestComponent testComp("prueba");
	EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	TextEvent event = TextEvent("\nEL MEJOR MENSAJE DE PRUEBA\n");
	EventManager::GetInstance()->EmitEvent(event);

	// Check double-add protection
	EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	EventManager::GetInstance()->EmitEvent(event);

	// Check remove
	EventManager::GetInstance()->UnregisterListener(&testComp, EventType::TEXT);
	EventManager::GetInstance()->EmitEvent(event);

	// Check clear
	EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	EventManager::GetInstance()->ClearListeners(EventType::TEXT);
	EventManager::GetInstance()->EmitEvent(event);
}

void Core::initLoadingTestScene()
{
	changeScene("test");
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
			InputManager::getInstance()->GeneralInputManagement(event);	//Se podr�a ir a pincho de forma mas especifica llamando directamente al de boton, tecla, etc
			break;
		}
	}

	// just avoid "window not responding"
	Ogre::WindowEventUtilities::messagePump();
}

bool Core::frameStarted(const Ogre::FrameEvent& evt)
{
	pollEvents();
	PhysicsManager::getInstance()->stepWorld();
	updateRender();

	audioManager->update();

	return true;
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

	try { ResourceManager::getInstance()->setup(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("ResourceManager setup fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try { InputManager::getInstance()->setup(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("InputManager setup fail \n" + (Ogre::String)e.what() + "\n");	return;
	}	

	sm = root->createSceneManager();

	ResourceManager::getInstance()->addSceneManager(sm);

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

void Core::updateRender()
{
	for (auto b: PhysicsManager::getInstance()->getBodies()) {
		btRigidBody* body = b.second;

		if (body && body->getMotionState()) {
			btTransform trans;
			body->getMotionState()->getWorldTransform(trans);

			void* userPointer = body->getUserPointer();
			if (userPointer) {
				btQuaternion orientation = trans.getRotation();
				Ogre::SceneNode* sceneNode = static_cast<Ogre::SceneNode*>(userPointer);
				sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
				sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
			}
		}
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
}


Ogre::Root* Core::getRoot()
{
	return root;
}

Ogre::SceneManager* Core::getSM()
{
	return sm;
}

Ogre::RenderWindow* Core::getOgreWin()
{
	return window;
}

SDL_Window* Core::getSDLWin()
{
	return sdlWindow;
}

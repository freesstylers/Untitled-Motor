#include "Core.h"


#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreBitesConfigDialog.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreCamera.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>

#include "TestComponent.h"
#include "EventManager.h"
#include "SphereBody.h"

Core::Core(const Ogre::String& appName) : appName(appName)
{
	resourceManager = new ResourceManager("./assets");
	inputManager = new InputManager();
	physicsManager = new PhysicsManager();
	audioManager = new AudioManager();
	root = nullptr;
}

Core::~Core()
{
	delete resourceManager;
	delete inputManager;
	delete physicsManager;
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

	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

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
	planeNode->showBoundingBox(true);

	//se le pasa una referencia al nodo al que esta ligado
	physicsManager->addBox(btVector3(planeNode->getPosition().x, planeNode->getPosition().y, planeNode->getPosition().z),
		btVector3(1080, 0, 800), 0)->setUserPointer(planeNode);


	//canicastanhazo = new Entity("canicastanhazo");

	Ogre::SceneNode* sphereNode = sm->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* sphereEntity = sm->createEntity("sphere.mesh");
	sphereEntity->setMaterialName("sphereTest");
	sphereNode->attachObject(sphereEntity);
	sphereNode->translate(Ogre::Vector3(0, 100, 0));
	float scaleFactor = 0.25;
	sphereNode->setScale(sphereNode->getScale() * scaleFactor);

	float rad = sphereEntity->getBoundingRadius();

	//canicastanhazo->addComponent<SphereBody>("spherebody", physicsManager, rad * scaleFactor / 2,
	//	btVector3(sphereNode->getPosition().x, sphereNode->getPosition().y, sphereNode->getPosition().z), 10, sphereNode);
	SphereBody* sp = new SphereBody("s", physicsManager, rad*scaleFactor/2,
		btVector3(sphereNode->getPosition().x, sphereNode->getPosition().y, sphereNode->getPosition().z), 10, sphereNode);

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
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				spawnBox();
				break;
			case SDLK_v:
				spawnSphere();
				break;
			default:
				break;
			}
		default:
			//llamar a InputManager
			inputManager->GeneralInputManagement(event);	//Se podría ir a pincho de forma mas especifica llamando directamente al de boton, tecla, etc
			break;
		}
	}

	// just avoid "window not responding"
	Ogre::WindowEventUtilities::messagePump();
}

bool Core::frameStarted(const Ogre::FrameEvent& evt)
{
	pollEvents();
	physicsManager->stepWorld();
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

void Core::spawnSphere()
{
	Ogre::SceneNode* sphereNode = sm->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* sphereEntity = sm->createEntity("sphere.mesh");
	sphereEntity->setMaterialName("sphereTest");
	sphereNode->attachObject(sphereEntity);
	sphereNode->translate(Ogre::Vector3(0, 100, 0));
	float scaleFactor = 0.25;
	sphereNode->setScale(sphereNode->getScale() * scaleFactor);

	float rad=sphereEntity->getBoundingRadius();

	//se le pasa una referencia al nodo al que esta ligado
	btRigidBody* rb=physicsManager->addSphere(sphereEntity->getBoundingRadius()*scaleFactor/2, 
		btVector3(sphereNode->getPosition().x, sphereNode->getPosition().y, sphereNode->getPosition().z),
		10);

	rb->setUserPointer(sphereNode);


}

void Core::spawnBox()
{
	Ogre::SceneNode* boxNode = sm->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* boxEntity = sm->createEntity("cube.mesh");
	boxEntity->setMaterialName("test");
	boxNode->attachObject(boxEntity);
	boxNode->translate(Ogre::Vector3(0, 100, 0));
	float scaleFactor = 0.25;
	boxNode->setScale(boxNode->getScale() * scaleFactor);

	Ogre::Vector3 size = boxEntity->getBoundingBox().getSize();

	//se le pasa una referencia al nodo al que esta ligado
	btRigidBody* rb=physicsManager->addBox(btVector3(boxNode->getPosition().x, boxNode->getPosition().y, boxNode->getPosition().z), 
		btVector3(boxEntity->getBoundingBox().getSize().x, boxEntity->getBoundingBox().getSize().y, boxEntity->getBoundingBox().getSize().z)*scaleFactor/2,
		10);
	rb->setUserPointer(boxNode);
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

void Core::updateRender()
{
	for (auto b: physicsManager->getBodies()) {
		btRigidBody* body = b;

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

#include "Core.h"


#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <stdexcept>


#include "ResourceManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "JsonFactoryParser.h"
#include "AudioManager.h"
#include "EventManager.h"
#include "Transform.h"
#include <iostream>

#include "RigidBody.h"


Core* Core::instance = 0;

Core::Core(const Ogre::String& appName) : appName(appName)
{
	root = nullptr;
	timer = new Ogre::Timer();
}

void Core::sceneCleanup()
{
	SceneManager::getInstance()->sceneCleanup();
}

Core::~Core()
{
	ResourceManager::clean();
	InputManager::clean();
	PhysicsManager::clean();
	SceneManager::clean();
	JsonFactoryParser::clean();
	AudioManager::clean();
	EventManager::clean();
	delete timer;
}
	
bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
{
	
	//Chamar a funcion de colision do componente rigidbody
	RigidBody* rb1 = static_cast<RigidBody*>(obj1->getCollisionObject()->getUserPointer());
	rb1->OnCollisionEnter(cp, obj1->getCollisionObject(), obj2->getCollisionObject());
	//rb1->getRigidBody()->activate(true);
	RigidBody* rb2 = static_cast<RigidBody*>(obj2->getCollisionObject()->getUserPointer());
	//rb2->getRigidBody()->activate(true);
	rb2->OnCollisionEnter(cp, obj1->getCollisionObject(), obj2->getCollisionObject());
	
	return false;
	
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

	try { PhysicsManager::setupInstance(); PhysicsManager::getInstance()->initWorld(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("PhysicsManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try { JsonFactoryParser::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("JsonFactoryParser init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try { AudioManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("AudioManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	try { EventManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("EventManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	setupRoot();

	if (checkConfig()) {
		setup();
	}

	gContactAddedCallback=callbackFunc;
}

void Core::changeScene(Ogre::String name)
{
	SceneManager::getInstance()->changeScene(name);
	SceneManager::getInstance()->getCurrentScene()->start();
}

void Core::initPhysicsTestScene()
{
	/*
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

	Ogre::Entity* plane = sm->createEntity("mPlane1080x800");
	Entity* terreno = new Entity("terreno");
	entities.push_back(terreno);

	Transform* t = new Transform("transform");
	t->setPosition(Ogre::Vector3(0, -100, 0));
	RenderComponent* r = new RenderComponent("render", sm, plane, "test");
	BoxBody* bbody = new BoxBody("body", physicsManager, btVector3(t->getPosition().x, t->getPosition().y, t->getPosition().z),
		btVector3(1080, 0, 800),0, btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK||btCollisionObject::CF_STATIC_OBJECT);
	terreno->addComponent<Transform>(t);
	terreno->addComponent<RenderComponent>(r);
	terreno->addComponent<BoxBody>(bbody);

	Entity* canicastanhazo = new Entity("canicastanhazo");
	entities.push_back(canicastanhazo);
	
	Transform* tr = new Transform("transform");
	tr->setScale(Ogre::Vector3(0.25, 0.25, 0.25));
	tr->setPosition(Ogre::Vector3(0, 100, 0));
	RenderComponent* rend = new RenderComponent("render", sm, "sphere.mesh", "sphereTest");
	SphereBody* sbody = new SphereBody("body", physicsManager, rend->getOgreEntity()->getBoundingRadius() * tr->getScale().x / 2,
		btVector3(tr->getPosition().x,  tr->getPosition().y, tr->getPosition().z), 10, btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	
	canicastanhazo->addComponent<Transform>(tr);
	canicastanhazo->addComponent<RenderComponent>(rend);
	canicastanhazo->addComponent<SphereBody>(sbody);

	Ogre::Light* luz = sm->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = sm->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
	*/
}

void Core::testMessageSystem() {
	//// Normal check
	//TestComponent testComp("prueba");
	//EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	//TextEvent event = TextEvent("\nEL MEJOR MENSAJE DE PRUEBA\n");
	//EventManager::GetInstance()->EmitEvent(event);

	//// Check double-add protection
	//EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	//EventManager::GetInstance()->EmitEvent(event);

	//// Check remove
	//EventManager::GetInstance()->UnregisterListener(&testComp, EventType::TEXT);
	//EventManager::GetInstance()->EmitEvent(event);

	//// Check clear
	//EventManager::GetInstance()->RegisterListener(&testComp, EventType::TEXT);
	//EventManager::GetInstance()->ClearListeners(EventType::TEXT);
	//EventManager::GetInstance()->EmitEvent(event);
}

void Core::initLoadingTestScene()
{
	changeScene("test");
}

void Core::start()
{
	Core::getInstance()->getRoot()->startRendering();
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
			Core::getInstance()->getRoot()->queueEndRendering();
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(sdlWindow)) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = window;
					win->windowMovedOrResized();
					windowResized(win);
				}
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				cout << "Totaltime " << getTime() << "\n";
				cout << "deltaTime " << deltaTime << "\n";
				//spawnBox();
				break;
			case SDLK_v:
				//spawnSphere();
				break;
			default:
				break;
			}
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
	deltaTime = getTime() - prevTime;

	prevTime = getTime();

	pollEvents();

	SceneManager::getInstance()->getCurrentScene()->preupdate();

	PhysicsManager::getInstance()->stepWorld();

	SceneManager::getInstance()->getCurrentScene()->physicsUpdate();

	SceneManager::getInstance()->getCurrentScene()->update();

	SceneManager::getInstance()->getCurrentScene()->lateUpdate();

	AudioManager::getInstance()->update();


	return true;
}

bool Core::checkConfig()
{
	if (!Core::getInstance()->getRoot()->restoreConfig())
	{
		return Core::getInstance()->getRoot()->showConfigDialog(nullptr);
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


	if (!(Core::getInstance()->getRoot()->restoreConfig() || Core::getInstance()->getRoot()->showConfigDialog(nullptr)))
		return;
}

void Core::setup()
{
	Core::getInstance()->getRoot()->initialise(false);
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

	sm = Core::getInstance()->getRoot()->createSceneManager();

	ResourceManager::getInstance()->addSceneManager(sm);

	Core::getInstance()->getRoot()->addFrameListener(this);
}

void Core::shutdown()
{

	if (window != nullptr)
	{
		Core::getInstance()->getRoot()->destroyRenderTarget(window);
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

	Ogre::ConfigOptionMap ropts = Core::getInstance()->getRoot()->getRenderSystem()->getConfigOptions();

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

	window = Core::getInstance()->getRoot()->createRenderWindow(windowName, w, h, false, &params);


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

void Core::updateRender()
{
	/*
	for (auto b : PhysicsManager::getInstance()->getBodies()) {
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
	*/
}

float Core::getTime()
{
	return timer->getMilliseconds();
}

float Core::getTimeDifference(float prevTime)
{
	return timer->getMilliseconds() - prevTime;
}

float Core::DeltaTime()
{
	return deltaTime;
}
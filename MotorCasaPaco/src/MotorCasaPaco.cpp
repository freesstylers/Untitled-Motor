#include "MotorCasaPaco.h"


#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <stdexcept>

#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Scene/SceneManager.h"
#include "Scene/JsonFactoryParser.h"
#include "Audio/AudioManager.h"
#include "Events/EventManager.h"
#include "GUI/GUI_Manager.h"
#include <iostream>

#include "Physics/RigidBody.h"


MotorCasaPaco* MotorCasaPaco::instance = 0;

MotorCasaPaco::MotorCasaPaco(const Ogre::String& appName) : appName(appName)
{
	root = nullptr;
	timer = new Ogre::Timer();
}

void MotorCasaPaco::sceneCleanup()
{
	SceneManager::getInstance()->sceneCleanup();
}

MotorCasaPaco::~MotorCasaPaco()
{
	ResourceManager::clean();
	InputManager::clean();
	PhysicsManager::clean();
	SceneManager::clean();
	JsonFactoryParser::clean();
	AudioManager::clean();
	EventManager::clean();
	GUI_Manager::clean();
	delete timer;
}
	
bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
{
	//Chamar a funcion de colision do componente rigidbody
	RigidBody* rb1;
	RigidBody* rb2;
	rb1 = static_cast<RigidBody*>(obj1->getCollisionObject()->getUserPointer());
	rb1->OnCollisionEnter(cp, obj1->getCollisionObject(), obj2->getCollisionObject());
	rb2 = static_cast<RigidBody*>(obj2->getCollisionObject()->getUserPointer());
	rb2->OnCollisionEnter(cp, obj1->getCollisionObject(), obj2->getCollisionObject());
	return false;
}

MotorCasaPaco* MotorCasaPaco::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool MotorCasaPaco::setupInstance(const Ogre::String& appName)
{
	if (instance == 0)
	{
		instance = new MotorCasaPaco(appName);
		return true;
	}

	return false;
}

void MotorCasaPaco::clean()
{
	delete instance;
}

void MotorCasaPaco::init()
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

	setupFactories();
}

void MotorCasaPaco::changeScene(Ogre::String name)
{
	GUI_Manager::getInstance()->loadLayout("SampleBrowserLoadScreen.layout");

	SceneManager::getInstance()->changeScene(name);
	SceneManager::getInstance()->getCurrentScene()->start();
}

void MotorCasaPaco::initLoadingTestScene()
{
	changeScene("test");
}

void MotorCasaPaco::start()
{
	MotorCasaPaco::getInstance()->getRoot()->startRendering();
}

void MotorCasaPaco::pollEvents()
{
	if (sdlWindow == nullptr)
		return;  // SDL events not initialized
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			MotorCasaPaco::getInstance()->getRoot()->queueEndRendering();
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
			case SDLK_p:
				resetTimer();
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

bool MotorCasaPaco::frameStarted(const Ogre::FrameEvent& evt)
{
	float prevTime = getTime();

	pollEvents();

	SceneManager::getInstance()->getCurrentScene()->preupdate();

	PhysicsManager::getInstance()->stepWorld();

	SceneManager::getInstance()->getCurrentScene()->physicsUpdate();

	SceneManager::getInstance()->getCurrentScene()->update();

	SceneManager::getInstance()->getCurrentScene()->lateUpdate();

	AudioManager::getInstance()->update();

	deltaTime = getTimeDifference(prevTime);

	return true;
}

bool MotorCasaPaco::checkConfig()
{
	if (!MotorCasaPaco::getInstance()->getRoot()->restoreConfig())
	{
		return MotorCasaPaco::getInstance()->getRoot()->showConfigDialog(nullptr);
	}
	else return true;
}


void MotorCasaPaco::setupRoot()
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

	if (!(MotorCasaPaco::getInstance()->getRoot()->restoreConfig() || MotorCasaPaco::getInstance()->getRoot()->showConfigDialog(nullptr)))
		return;
}

void MotorCasaPaco::setup()
{
	MotorCasaPaco::getInstance()->getRoot()->setRenderSystem(MotorCasaPaco::getInstance()->getRoot()->getRenderSystemByName("OpenGL Rendering Subsystem"));

	MotorCasaPaco::getInstance()->getRoot()->initialise(false);
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

	try { GUI_Manager::setupInstance(MotorCasaPaco::getInstance()->getOgreWin()); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("UIManager init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	sm = MotorCasaPaco::getInstance()->getRoot()->createSceneManager();

	sm->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	sm->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	MotorCasaPaco::getInstance()->getSM()->setShadowFarDistance(1000000);

	ResourceManager::getInstance()->addSceneManager(sm);

	MotorCasaPaco::getInstance()->getRoot()->addFrameListener(this);
}

void MotorCasaPaco::shutdown()
{

	if (window != nullptr)
	{
		MotorCasaPaco::getInstance()->getRoot()->destroyRenderTarget(window);
		window = nullptr;
	}

	if (sdlWindow != nullptr)
	{
		SDL_DestroyWindow(sdlWindow);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		sdlWindow = nullptr;
	}
}


void MotorCasaPaco::setupWindow(Ogre::String windowName)
{
	uint32_t w, h;

	Ogre::ConfigOptionMap ropts = MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->getConfigOptions();

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

	window = MotorCasaPaco::getInstance()->getRoot()->createRenderWindow(windowName, w, h, false, &params);

	//////////por si queremos que la ventana oculte el cursor
	SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
	SDL_ShowCursor(true);
}


Ogre::Root* MotorCasaPaco::getRoot()
{
	return root;
}

Ogre::SceneManager* MotorCasaPaco::getSM()
{
	return sm;
}

Ogre::RenderWindow* MotorCasaPaco::getOgreWin()
{
	return window;
}

SDL_Window* MotorCasaPaco::getSDLWin()
{
	return sdlWindow;
}

float MotorCasaPaco::getTime()
{
	return timer->getMicroseconds()/1000.0f;
}

float MotorCasaPaco::getTimeDifference(float prevTime)
{
	return timer->getMicroseconds()/1000.0f - prevTime;
}

float MotorCasaPaco::DeltaTime()
{
	return deltaTime;
}

void MotorCasaPaco::resetTimer()
{
	timer->reset();
}

void MotorCasaPaco::setFarShadowDistance(Ogre::Real dist)
{
	sm->setShadowFarDistance(dist);
}

void MotorCasaPaco::setShadowTechnique(Ogre::ShadowTechnique type)
{
	sm->setShadowTechnique(type);
}

Ogre::Real MotorCasaPaco::getFarShadowDistance()
{
	return sm->getShadowFarDistance();
}

Ogre::ShadowTechnique MotorCasaPaco::getShadowTechnique()
{
	return sm->getShadowTechnique();
}

#include "Entity/Factory.h"

#include "Entity/Transform.h"
#include "Graphics/Mesh.h"
#include "Physics/RigidBody.h"
#include "Graphics/Camera.h"
#include "Audio/AudioComponent.h"
#include "Audio/AudioListenerComponent.h"
#include "Graphics/Light.h"
#include "Others/TerrainRotation.h"
#include "Others/SimpleMovement.h"
#include "Others/ForcesTest.h"

class TransformFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Transform(args);
	};
};
class MeshFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Mesh(args);
	};
};
class RigidBodyFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RigidBody(args);
	};
};
class CameraFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Camera(args);
	};
};
class AudioComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new AudioComponent(args);
	};
};
class AudioListenerComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new AudioListenerComponent(args);
	};
};

class TerrainRotationFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new TerrainRotation(args);
	};
};

class SimpleMovementFactory : public BaseFactory
{
	Component* createComponent(json& args) override
	{
		return new SimpleMovement(args);
	}
};
class ForcesTestFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ForcesTest(args);
	};
};
class LightFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Light(args);
	};
};

void MotorCasaPaco::setupFactories()
{
	JsonFactoryParser* j = JsonFactoryParser::getInstance();

	j->addFactory("Transform", new TransformFactory());
	j->addFactory("Mesh", new MeshFactory());
	j->addFactory("RigidBody", new RigidBodyFactory());
	j->addFactory("Camera", new CameraFactory());
	j->addFactory("AudioComponent", new AudioComponentFactory());
	j->addFactory("AudioListenerComponent", new AudioListenerComponentFactory());
	j->addFactory("TerrainRotation", new TerrainRotationFactory());
	j->addFactory("SimpleMovement", new SimpleMovementFactory());
	j->addFactory("ForcesTest", new ForcesTestFactory());
	j->addFactory("Light", new LightFactory());
}
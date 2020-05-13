#include "MotorCasaPaco.h"

#include <SDL.h>
#include <SDL_video.h>
#include <SDL_syswm.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h>
#include <OgreMeshManager.h>
#include <OgreTimer.h>
#include <OgreMesh.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <stdexcept>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <OgreViewport.h>

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
#include "Graphics/PacoFrameListener.h"
#include "checkML.h"

using namespace std;
MotorCasaPaco* MotorCasaPaco::instance = 0;

MotorCasaPaco::MotorCasaPaco(const std::string& appName) : appName(appName)
{
	frameListener_ = new PacoFrameListener();
	root = nullptr;
}

void MotorCasaPaco::currentSceneCleanup()
{
	SceneManager::getInstance()->sceneCleanup();
}

MotorCasaPaco::~MotorCasaPaco()
{
	SceneManager::clean();
	GUI_Manager::clean();


	ResourceManager::clean();

	delete root;

	InputManager::clean();
	PhysicsManager::clean();
	JsonFactoryParser::clean();
	AudioManager::clean();
	EventManager::clean();


	delete frameListener_; frameListener_ = nullptr;

	SDL_Quit();

}
	
bool callbackFunc(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
{
	//Chamar a funcion de colision do componente rigidbody
	RigidBody* rb1;
	RigidBody* rb2;
	void* point1 = obj1->getCollisionObject()->getUserPointer();
	void* point2 = obj2->getCollisionObject()->getUserPointer();

	if (point1 == nullptr || point2 == nullptr) return false;

	rb1 = static_cast<RigidBody*>(point1);
	if (rb1->getEntity() == nullptr)
		return false;

	rb2 = static_cast<RigidBody*>(point2);
	if (rb2->getEntity() == nullptr)
		return false;

	rb1->getEntity()->OnCollision(rb2->getEntity());
	rb2->getEntity()->OnCollision(rb1->getEntity());

	return false;
}

MotorCasaPaco* MotorCasaPaco::getInstance()
{
	if (instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool MotorCasaPaco::setupInstance(const std::string& appName)
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
	SDL_Init(SDL_INIT_EVERYTHING);

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

void MotorCasaPaco::changeScene(std::string name)
{
	SceneManager::getInstance()->changeScene(name);
	EventManager::getInstance()->EmitEvent("changeScene");
}

void MotorCasaPaco::initLoadingTestScene()
{
	changeScene("UITest");
}

void MotorCasaPaco::start(std::string initialScene)
{
	SceneManager::getInstance()->start(initialScene);
	MotorCasaPaco::getInstance()->getRoot()->startRendering();
}

void MotorCasaPaco::exit()
{
	MotorCasaPaco::getInstance()->getRoot()->queueEndRendering();
}

void MotorCasaPaco::processFrame()
{
	pollEvents();

	if (!paused_) {
		SceneManager::getInstance()->preUpdate();

		PhysicsManager::getInstance()->stepWorld();

		SceneManager::getInstance()->physicsUpdate();

		SceneManager::getInstance()->update();

		SceneManager::getInstance()->lateUpdate();
	}
	else
		SceneManager::getInstance()->pausedUpdate();

	SceneManager::getInstance()->alwaysLateUpdate();

	AudioManager::getInstance()->update();

	SceneManager::getInstance()->deleteEntities();

	GUI_Manager::getInstance()->update(DeltaTime());

	SceneManager::getInstance()->endFrame();
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
				/*if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = window;
					win->windowMovedOrResized();
					frameListener_->windowResized(win);
				}*/
			}
			break;
		default:
			//llamar a InputManager
			InputManager::getInstance()->GeneralInputManagement(event);	//Se podr�a ir a pincho de forma mas especifica llamando directamente al de boton, tecla, etc
			break;
		}
	}

	// just avoid "window not responding"
	//Ogre::WindowEventUtilities::messagePump();
}

bool MotorCasaPaco::checkConfig()
{
	if (!MotorCasaPaco::getInstance()->getRoot()->restoreConfig())
	{
		return MotorCasaPaco::getInstance()->getRoot()->showConfigDialog(nullptr);
	}
	else return true;
}

void MotorCasaPaco::extraConfig(json& j)
{
	if (!j["FullScreen"].is_null())
	{
		if (j["FullScreen"] == "Si")
		{

			fullScreen = true;
		}
		else if (j["FullScreen"] == "No")
		{

			fullScreen = false;
		}
	}

	if (!j["Shadows"].is_null())
	{
		/*if (j["Shadows"] == "No")
		{
			sm->setShadowTechnique(Ogre::SHADOWTYPE_NONE);
		}
		else
		{
			sm->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
			MotorCasaPaco::getInstance()->getSM()->setShadowFarDistance(1000000);

			if (j["Shadows"] == "Bajo")
			{
				sm->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
			}
			else if (j["Shadows"] == "Medio")
			{
				sm->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
			}
			else if (j["Shadows"] == "Alto")
			{
				sm->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
			}
		}*/
		
		std::string interm = j["Shadows"];
		shadows = interm;
	}

	if (!j["DrawDistance"].is_null())
	{
		if (j["DrawDistance"] == "Bajo")
		{
		}
		else if (j["DrawDistance"] == "Normal")
		{
		}
		else if (j["DrawDistance"] == "Alto")
		{
		}
	}

	if (!j["Reflections"].is_null() && j["Reflections"] != "No")
	{
		if (j["Reflections"] == "Bajo")
		{
		}
		else if (j["Reflections"] == "Normal")
		{
		}
		else if (j["Reflections"] == "Alto")
		{
		}
	}

	if (!j["Filter"].is_null() && j["Filter"] != "No")
	{
		//Filtro
	}


	if (!j["ShowFPS"].is_null() && j["ShowFPS"] != "No")
	{
		//Show FPS
	}
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
	MotorCasaPaco::getInstance()->getRoot()->initialise(false);

	json j;
	std::ifstream i("config.cfg");

	if (i.is_open())
	{
		i >> j;
		i.close();
	}
	else
	{
		std::cout << "File not found: config.cfg\n";
	}

	BackupExtraConfig = j;
	ExtraConfig = j;

	extraConfig(j);

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

	ResourceManager::getInstance()->addSceneManager(sm);

	MotorCasaPaco::getInstance()->getRoot()->addFrameListener(frameListener_);

	if (fullScreen)
		setFullScreenOn();
	else
		setFullScreenOff();
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

void MotorCasaPaco::setupWindow(std::string windowName)
{
	storeGraphicsConfiguration();

	if (!SDL_WasInit(SDL_INIT_VIDEO))
		SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE

	sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	Ogre::NameValuePairList params;

	params["FSAA"] = CurrentGraphicsConfiguration["FSAA"].currentValue;
	params["vsync"] = CurrentGraphicsConfiguration["VSync"].currentValue;
	params["gamma"] = CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue;

	params["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	window = MotorCasaPaco::getInstance()->getRoot()->createRenderWindow(windowName, screen_width, screen_height, false, &params);

	//////////por si queremos que la ventana oculte el cursor
	SDL_SetWindowGrab(sdlWindow, SDL_bool(false));
	SDL_ShowCursor(false);
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

GUI_Manager* MotorCasaPaco::getGUI_Manager()
{
	return GUI_Manager::getInstance();
}

ResourceManager* MotorCasaPaco::getResourceManager()
{
	return ResourceManager::getInstance();
}

SceneManager* MotorCasaPaco::getSceneManager()
{
	return SceneManager::getInstance();
}

InputManager* MotorCasaPaco::getInputManager()
{
	return InputManager::getInstance();
}

AudioManager* MotorCasaPaco::getAudioManager()
{
	return AudioManager::getInstance();
}

float MotorCasaPaco::getTime()
{
	return frameListener_->getTime();
}

float MotorCasaPaco::getTimeDifference(float prevTime)
{
	return frameListener_->getTimeDifference(prevTime);
}

float MotorCasaPaco::DeltaTime()
{
	return 	frameListener_->DeltaTime();
}

void MotorCasaPaco::resetTimer()
{
	frameListener_->resetTimer();
}

void MotorCasaPaco::pause()
{
	paused_ = !paused_;
}

bool MotorCasaPaco::isPaused() {
	return paused_;
}

void MotorCasaPaco::resize(int width, int height)
{
	SDL_SetWindowSize(sdlWindow, width, height);
	//window->resize(width, height);
	window->windowMovedOrResized();
//	getOgreWin()->getViewport(0)->setDimensions(0,0,width, height);

	GUI_Manager::getInstance()->setDefaultFont(width);

	GUI_Manager::getInstance()->updateScreenSize(width, height);
}

void MotorCasaPaco::setFullScreenOn()
{
	SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
	resize(screen_width, screen_height);
	MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->setConfigOption("Full Screen", "Yes");
}

void MotorCasaPaco::setFullScreenOff()
{
	resize(screen_width, screen_height);
	!SDL_SetWindowFullscreen(sdlWindow, !SDL_WINDOW_FULLSCREEN);
	MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->setConfigOption("Full Screen", "No");
}

bool MotorCasaPaco::getFullScreen()
{
	return fullScreen;
}

void MotorCasaPaco::setFullScreen(bool value)
{
	fullScreen = value;
}

bool MotorCasaPaco::getVSync()
{
	return vSync;
}

std::string MotorCasaPaco::getVSync(bool value)
{
	std::string r;

	if (value)
		r = "Yes";
	else
		r = "No";

	return r;
}

void MotorCasaPaco::setVSync(bool value)
{
	vSync = value;
}

void MotorCasaPaco::setVSync(std::string value)
{
	if (value == "Yes")
		vSync = true;
	else if (value == "No")
		vSync = false;
}

void MotorCasaPaco::setVSyncOn()
{
	SDL_GL_SetSwapInterval(1);
	MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->setConfigOption("VSync", "Yes");
}

void MotorCasaPaco::setVSyncOff()
{
	SDL_GL_SetSwapInterval(0);
	MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->setConfigOption("VSync", "No");
}

void MotorCasaPaco::writeGraphicOptions()
{
	ofstream outputFile;

	#ifdef  _DEBUG
		outputFile.open("window_d.cfg");
	#else
		outputFile.open("window.cfg");
	#endif

	outputFile << "Render System=OpenGL Rendering Subsystem\n";
	outputFile << "[OpenGL Rendering Subsystem]\n";
	outputFile << "Colour Depth=32\n"; //Unica opcion
	outputFile << "Display Frequency=N/A\n"; //Unica opcion
	outputFile << "FSAA=" << CurrentGraphicsConfiguration["FSAA"].currentValue << "\n"; //El 0 es opcion, pero aun no esta hecha
	outputFile << "Full Screen=No\n"; //No le gusta otra opcion, asi que se hace a traves de config.cfg
	outputFile << "RTT Preferred Mode=FBO\n"; //Unica opcion
	outputFile << "VSync=" << CurrentGraphicsConfiguration["VSync"].currentValue << "\n";
	outputFile << "VSync Interval=1\n"; //Esto que hace xd
	outputFile << "Video Mode=" << CurrentGraphicsConfiguration["Video Mode"].currentValue << "\n";
	outputFile << "sRGB Gamma Conversion=" << CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue << "\n";

	outputFile.close();
}

json MotorCasaPaco::writeExtraOptions()
{
	ofstream outputFile;

	outputFile.open("config.cfg");

	outputFile << "{\n";
	if (fullScreen)
		outputFile << "\"FullScreen\" : \"" << "Si" << "\",\n";
	else
		outputFile << "\"FullScreen\" : \"" << "No" << "\",\n";
	outputFile << "\"Shadows\" : \"" << "Medio" << "\",\n";
	outputFile << "\"DrawDistance\" : \"" << "Medio" << "\",\n";
	outputFile << "\"Reflections\" : \"" << "No" << "\",\n";
	outputFile << "\"Filter\" : \"" << "No" << "\",\n";
	outputFile << "\"ShowFPS\" : \"" << "No" << "\"\n";
	outputFile << "}";

	outputFile.close();

	json j;
	std::ifstream i("config.cfg");

	i >> j;
	i.close();

	return j;
}

std::string MotorCasaPaco::getScreenProportion()
{
	return screen_proportion;
}

std::string MotorCasaPaco::getFullScreen(bool value)
{
	std::string r;

	if (value)
		r = "Yes";
	else
		r = "No";

	return r;
}

void MotorCasaPaco::setScreenProportion(std::string value)
{
	screen_proportion = value;
}

void MotorCasaPaco::setScreenProportion(int height)
{
	if (height == 1024)
		screen_proportion = "5 : 4";
	else if (height == 1050 || height == 800)
		screen_proportion = "16 : 10";
	else if (height == 1080 || height == 900 || height == 720)
		screen_proportion = "16 : 9";
	else if (height == 872 || height == 768 || height == 624 || height == 600 || height == 480)
		screen_proportion = "4 : 3";
}

std::string MotorCasaPaco::getResolution()
{
	return video_mode;
}

void MotorCasaPaco::setResolution(std::string value)
{
	video_mode = value;

	std::stringstream mode(value);

	Ogre::String token;
	mode >> screen_width;
	mode >> token;
	mode >> screen_height;

	//MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->setConfigOption("Video Mode", video_mode);
}

int MotorCasaPaco::getScreenWidth()
{
	return screen_width;
}

int MotorCasaPaco::getScreenHeight()
{
	return screen_height;
}

std::string MotorCasaPaco::getFSAA()
{
	return fsaa;
}

void MotorCasaPaco::setFSAA(int value)
{
	switch (value)
	{
	case 0:
	{
		fsaa = "0";
	}
	break;
	case 2:
	{
		fsaa = "2";
	}
	break;
	case 4:
	{
		fsaa = "4";
	}
	break;
	case 8:
	{
		fsaa = "8";
	}
	break;
	}

	CurrentGraphicsConfiguration["FSAA"].currentValue = fsaa;
}

void MotorCasaPaco::setFSAA(std::string value)
{
	fsaa = value;
	CurrentGraphicsConfiguration["FSAA"].currentValue = fsaa;
}

bool MotorCasaPaco::getGamma()
{
	return gamma;
}

void MotorCasaPaco::setGamma(bool value)
{
	std::string v;
	if (value)
		v = "Yes";
	else
		v = "No";

	gamma = value;
	CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue = v;
}

std::string MotorCasaPaco::getShadows()
{
	return shadows;
}

void MotorCasaPaco::setShadows(std::string value)
{
	shadows = value;
}

void MotorCasaPaco::changeGraphicComponents()
{
	//FullScreen
	if (fullScreen) //A Pantalla Completa
	{
		setFullScreenOn();
		CurrentGraphicsConfiguration["Full Screen"].currentValue = "Yes";
	}
	else //A Modo Ventana
	{
		setFullScreenOff();
		CurrentGraphicsConfiguration["Full Screen"].currentValue = "No";
	}

	if (CurrentGraphicsConfiguration["Video Mode"].currentValue != video_mode)
	{
		if (fullScreen)
		{
			setFullScreenOff();
			resize(screen_width, screen_height);
			setFullScreenOn();
		}
		else
		{
			resize(screen_width, screen_height);
		}

		CurrentGraphicsConfiguration["Video Mode"].currentValue = video_mode;

	}

	if (CurrentGraphicsConfiguration["VSync"].currentValue != getVSync(vSync))
	{
		if (vSync)
		{
			setVSyncOn();
			CurrentGraphicsConfiguration["VSync"].currentValue = "Yes";
		}
		else
		{
			setVSyncOff();
			CurrentGraphicsConfiguration["VSync"].currentValue = "No";
		}
		//Mensaje de reiniciar aplicacion?
		//Tooltip en menú?
	}

	writeGraphicOptions();
	BackupGraphicsConfiguration = CurrentGraphicsConfiguration;
	writeExtraOptions();
	BackupExtraConfig = ExtraConfig;
}

void MotorCasaPaco::changeAdvancedGraphicComponents()
{
	/*
	
	Stuff

	*/
	BackupGraphicsConfiguration = CurrentGraphicsConfiguration;
	ExtraConfig	= writeExtraOptions();
}

void MotorCasaPaco::revertGraphicChanges()
{
	CurrentGraphicsConfiguration = BackupGraphicsConfiguration;

	video_mode = CurrentGraphicsConfiguration["Video Mode"].currentValue;
	
	std::stringstream mode(video_mode);

	Ogre::String token;
	mode >> screen_width;
	mode >> token;
	mode >> screen_height;

	setScreenProportion(screen_height);

	if (CurrentGraphicsConfiguration["Full Screen"].currentValue == "Yes")
		fullScreen = true;
	else if (CurrentGraphicsConfiguration["Full Screen"].currentValue == "No")
		fullScreen = false;

	if (CurrentGraphicsConfiguration["VSync"].currentValue == "Yes")
		vSync = true;
	else if (CurrentGraphicsConfiguration["VSync"].currentValue == "No")
		vSync = false;
}

void MotorCasaPaco::revertAdvancedGraphicChanges()
{
	CurrentGraphicsConfiguration = BackupGraphicsConfiguration;

	fsaa = CurrentGraphicsConfiguration["FSAA"].currentValue;

	if (CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue == "Yes")
		gamma = true;
	else if (CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue == "No")
		gamma = false;

	ExtraConfig = BackupExtraConfig;
	extraConfig(ExtraConfig);
}

void MotorCasaPaco::storeGraphicsConfiguration()
{
	CurrentGraphicsConfiguration = MotorCasaPaco::getInstance()->getRoot()->getRenderSystem()->getConfigOptions();
	BackupGraphicsConfiguration = CurrentGraphicsConfiguration;

	fsaa = CurrentGraphicsConfiguration["FSAA"].currentValue;

	if (CurrentGraphicsConfiguration["VSync"].currentValue == "Yes")
		vSync = true;
	else if (CurrentGraphicsConfiguration["VSync"].currentValue == "No")
		vSync = false;

	if (CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue == "Yes")
		gamma = true;
	else if (CurrentGraphicsConfiguration["sRGB Gamma Conversion"].currentValue == "No")
		gamma = false;

	std::istringstream mode(CurrentGraphicsConfiguration["Video Mode"].currentValue);
	video_mode = CurrentGraphicsConfiguration["Video Mode"].currentValue;

	Ogre::String token;
	mode >> screen_width;
	mode >> token;
	mode >> screen_height;

	setScreenProportion(screen_height);
}

void MotorCasaPaco::setFarShadowDistance(float dist)
{
	sm->setShadowFarDistance(dist);
}

void MotorCasaPaco::setShadowTechnique(Ogre::ShadowTechnique type)
{
	sm->setShadowTechnique(type);
}

float MotorCasaPaco::getFarShadowDistance()
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
#include "Scene/Skybox.h"

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

class LightFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Light(args);
	};
};
class SkyboxFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Skybox(args);
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
	j->addFactory("Light", new LightFactory());
	j->addFactory("Skybox", new SkyboxFactory());
}
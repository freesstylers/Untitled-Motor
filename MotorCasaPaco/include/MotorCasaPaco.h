#pragma once

#include <string>

#include "Entity/Entity.h"

class PacoFrameListener;
class GUI_Manager;
class ResourceManager;
class SceneManager;
class InputManager;
class AudioManager;

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
	struct ConfigOption;
	typedef std::map<std::string, std::string> NameValuePairList;
	typedef std::map< std::string, ConfigOption > ConfigOptionMap;
	enum ShadowTechnique;
}

class SDL_Window;

class MotorCasaPaco
{

public:
	~MotorCasaPaco();

	static MotorCasaPaco* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();

	void init();

	void changeScene(std::string name);

	void initLoadingTestScene();

	void start();
	void exit();
	void pollEvents();

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSM();
	Ogre::RenderWindow* getOgreWin();
	SDL_Window* getSDLWin();
	GUI_Manager* getGUI_Manager();
	ResourceManager* getResourceManager();
	SceneManager* getSceneManager();
	InputManager* getInputManager();
	AudioManager* getAudioManager();

	float getTime();
	float getTimeDifference(float prevTime);
	float DeltaTime();
	void resetTimer();

	void resize(int width, int height);
	void setFullScreenOn();
	void setFullScreenOff();
	bool getFullScreen();
	void setFullScreen(bool value);
	bool getVSync();
	std::string getVSync(bool value);
	void setVSync(bool value);
	void setVSync(std::string value);
	void setVSyncOn();
	void setVSyncOff();
	void writeGraphicOptions();
	Ogre::ConfigOptionMap getGraphicsConfiguration();
	Ogre::ConfigOptionMap getBackupGraphicsConfiguration();
	std::string getScreenProportion();
	std::string getFullScreen(bool value);
	void setScreenProportion(std::string value);
	void setScreenProportion(int height);
	std::string getResolution();
	void setResolution(std::string value);
	void updateGraphicTexts();
	void updateAdvancedGraphicTexts();

	void changeGraphicComponents();
	void changeAdvancedGraphicComponents();


	void setFarShadowDistance(float dist);
	void setShadowTechnique(Ogre::ShadowTechnique type);
	float getFarShadowDistance();
	Ogre::ShadowTechnique getShadowTechnique();

private:

	MotorCasaPaco(const std::string& appName);

	void sceneCleanup();

	void setupWindow(std::string windowName);
	void setupRoot();
	void setup();
	void shutdown();
	bool checkConfig();

	void setupFactories();

	Ogre::Root* root;
	Ogre::SceneManager* sm;

	SDL_Window* sdlWindow;
	Ogre::RenderWindow* window;
	std::string appName;
	static MotorCasaPaco* instance;
	PacoFrameListener* frameListener_;

	void storeGraphicsConfiguration();

	//Screen Stuff
	Ogre::ConfigOptionMap CurrentGraphicsConfiguration;
	Ogre::ConfigOptionMap BackupGraphicsConfiguration;
	bool fullScreen;
	bool vSync;
	int screen_width;
	int screen_height;
	std::string screen_proportion;
	std::string video_mode;
};


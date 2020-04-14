#pragma once

#include <string>

#include "Entity/Entity.h"

class PacoFrameListener;
class GUI_Manager;

namespace Ogre {
	class Root;
	class SceneManager;
	class RenderWindow;
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

	void pollEvents();

	Ogre::Root* getRoot();
	Ogre::SceneManager* getSM();
	Ogre::RenderWindow* getOgreWin();
	SDL_Window* getSDLWin();
	GUI_Manager* getGUI_Manager();

	float getTime();
	float getTimeDifference(float prevTime);
	float DeltaTime();
	void resetTimer();

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
};


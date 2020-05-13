#pragma once

#include <string>

#include "Others/json.hpp"
#include "Scene/Scene.h"

class SceneManager
{
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	Scene* getCurrentScene();

	void sceneCleanup();

	Scene* loadScene(const std::string& sceneName);
	void changeScene(const std::string& name);

	void start(std::string initialScene);
	void preUpdate();
	void physicsUpdate();
	void update();
	void lateUpdate();
	void pausedUpdate();
	void alwaysLateUpdate();
	void endFrame();
	void deleteEntities();

private:
	SceneManager();
	static SceneManager* instance;

	Scene* currentScene_ = nullptr;

	void processChangeSceneRequest();

	bool changeSceneRequested_ = false;
	std::string nextScene_ = "";
};


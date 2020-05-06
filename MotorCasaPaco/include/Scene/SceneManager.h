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

	Scene* loadScene(const std::string& scene);

	Scene* getCurrentScene();

	void sceneCleanup();

	void changeScene(const std::string& name);

	void start(std::string initialScene);
	void preUpdate();
	void physicsUpdate();
	void update();
	void lateUpdate();
	void endFrame();

private:
	SceneManager();
	static SceneManager* instance;
	
	void processChangeSceneRequest();
	Scene* currentScene_ = nullptr;

	bool changeSceneRequested_ = false;
	std::string nextScene_ = "";
};


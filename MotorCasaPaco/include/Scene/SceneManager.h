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

	void changeScene(const  std::string& name);

private:
	SceneManager();
	static SceneManager* instance;
	
	Scene* currentScene;
};


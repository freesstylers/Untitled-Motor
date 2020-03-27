#pragma once

#include "Scene.h"

#include <json.hpp>

using json = nlohmann::json;

class SceneManager
{
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	Scene* loadScene(const Ogre::String& scene);

	Scene* getCurrentScene();

	void sceneCleanup();

	void changeScene(const Ogre::String& name);

private:
	SceneManager();


	Scene* currentScene;

	static SceneManager* instance;
};

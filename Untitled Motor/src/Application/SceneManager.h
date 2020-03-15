#pragma once

#include "Entity.h"


#include <json.hpp>

using json = nlohmann::json;

class SceneManager
{
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	void loadScene(const json& scene);

	json getCurrentScene();

private:
	SceneManager();


	json currentScene;

	static SceneManager* instance;
};


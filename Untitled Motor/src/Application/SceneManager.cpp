#include "SceneManager.h"

SceneManager* SceneManager::instance = 0;

SceneManager::~SceneManager()
{
}

SceneManager::SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool SceneManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new SceneManager();
		return true;
	}

	return false;
}

void SceneManager::clean()
{
	delete instance;
}

void SceneManager::loadScene(const json& scene)
{
	currentScene = scene;

	//call factories (one for entity and one for comps? Entity gets transform?
	//load prefabs
	//load components
}

json SceneManager::getCurrentScene()
{
	return currentScene;
}

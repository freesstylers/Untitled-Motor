#include "SceneManager.h"


#include "ResourceManager.h"

SceneManager* SceneManager::instance = 0;

SceneManager::~SceneManager()
{
	sceneCleanup();
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

Scene* SceneManager::loadScene(const Ogre::String& scene)
{
	json j = ResourceManager::getInstance()->loadSceneFile(scene);

	currentScene = new Scene();
	currentScene->setupScene(j);

	return currentScene;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::sceneCleanup()
{
	delete currentScene;
	currentScene = nullptr;
}

void SceneManager::changeScene(const Ogre::String& name)
{
	sceneCleanup();
	currentScene = loadScene(name);
}

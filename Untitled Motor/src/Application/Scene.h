#pragma once
#include "Entity.h"
#include <vector>
#include <OgreCamera.h>

#include <json.hpp>

using json = nlohmann::json;

class Core;

class Scene
{
public:
	Scene();
	~Scene();

	void setupScene(const json& j);

private:
	Ogre::Camera* cam;
	Ogre::Viewport* vp;

	Ogre::Root* root;
	Ogre::SceneManager* sm;
	Ogre::RenderWindow* window;

	std::vector<Entity*> entities;
};


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

	void setupScene(json& j);

	Ogre::Camera* getCam();
	Ogre::Viewport* getVP();
	Entity* getEntity(const std::string& name);

private:

	Entity* createEntity(json& j);
	void createCam(json& j);

	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	std::map<std::string, Entity*> entities;

	Ogre::String name;
};


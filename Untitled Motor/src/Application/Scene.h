#pragma once
#include <json.hpp>

#include "Entity.h"
#include <vector>
#include <OgreCamera.h>


using json = nlohmann::json;

class Core;

class Scene
{
public:
	Scene();
	~Scene();

	void setupScene(json& j);

	Entity* getEntity(const std::string& name);

	void start();
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();

private:

	Entity* createEntity(json& j);

	std::map<std::string, Entity*> entities;

	Ogre::String name;
};


#pragma once
#include <vector>
#include <string>

#include "Others/json.hpp"
#include "Entity/Entity.h"

class MotorCasaPaco;

class Scene
{
public:
	Scene();
	~Scene();

	void setupScene(json& j);

	Entity* getEntity(const std::string& name);
	Entity* createEntity(json& j);
	void addEntity(std::string name);

	void start();
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();

private:
	std::map<std::string, Entity*> entities;
	std::string name;
	int addedEntitiesCounter = 0;
};


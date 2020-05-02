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
	Entity* addEntity(std::string name, std::string tag = "Untagged", bool callStart = true);
	bool deleteEntity(const std::string name);
	std::string getName() const;

	void start();
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();

private:
	std::map<std::string, Entity*> entities;
	std::vector<Entity*> entitiesWithoutParent_; // Used recursively enable all entities on start
	std::string name;
	int addedEntitiesCounter = 0;

	void recursivelyActivateEntities(Entity* ent);
};


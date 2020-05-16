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
	std::list<Entity*> getEntitiesByTag(const std::string& tag);
	Entity* createEntity(json& j);
	Entity* addEntity(std::string name, std::string tag = "Untagged", bool callStart = true);
	bool deleteEntity(const std::string name);
	std::string getName() const;

	void start();
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();
	void pausedUpdate();
	void alwaysLateUpdate();
	void deleteInstances();

private:
	std::map<std::string, Entity*> entities;
	std::map<std::string, Entity*> executioner;
	std::vector<Entity*> entitiesWithoutParent_; // Used recursively enable all entities on start
	std::string name;
	int addedEntitiesCounter = 0;

	void recursivelyActivateEntities(Entity* ent);
};


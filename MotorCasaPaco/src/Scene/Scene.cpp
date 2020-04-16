#include "Scene/Scene.h"

#include <functional>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
//#include <OgreCamera.h>

#include "MotorCasaPaco.h"
#include "Resources/ResourceManager.h"
#include <GUI/GUI_Manager.h>
#include "checkML.h"

using namespace std;

Scene::Scene()
{
}

Scene::~Scene()
{
	MotorCasaPaco::getInstance()->getOgreWin()->removeAllViewports();
	//delete cam;
	entities.clear();
}

void Scene::setupScene(json& j)
{
	std::string interm = j["name"];
	name = interm;

	if (!j["entities"].is_null() && j["entities"].is_array()) {
		std::vector<json> e = j["entities"];
		for (json ent : e) {

			if (entities.find(ent["name"]) == entities.end())
				entities.erase(ent["name"]);

			entities[ent["name"]] = createEntity(ent);
		}

		// Set the parents after all entities are loaded to avoid order problems
		for (json ent : e) {
			if (!ent["parent"].is_null())
				entities[ent["name"]]->setParent(ent["parent"]);
		}
	}
	
	if (!j["UI"].is_null() && j["UI"].is_array()) {
		std::vector<json> e = j["UI"];
		for (json UI_Elem : e) {
			MotorCasaPaco::getInstance()->getGUI_Manager()->addChild(UI_Elem["type"], UI_Elem["route"]);
		}
	}
}

Entity* Scene::getEntity(const std::string& name)
{
	std::map<string, Entity*>::iterator entity = entities.find(name);
	if (entity == entities.end())
		return nullptr;
	else
		return entity->second;
}

void Scene::start() {
	for (pair<string, Entity*> e : entities) {
		e.second->start();
	}
}

void Scene::preupdate()
{
	for (pair<string, Entity*> e : entities) {
		e.second->preupdate();
	}
}

void Scene::physicsUpdate()
{
	for (pair<string, Entity*> e : entities) {
		e.second->physicsUpdate();
	}
}

void Scene::update()
{
	for (pair<string, Entity*> e : entities) {
		e.second->update();
	}
}

void Scene::lateUpdate()
{
	for (pair<string, Entity*> e : entities) {
		e.second->lateUpdate();
	}
}

Entity* Scene::createEntity(json& j)
{
	Entity* ent = new Entity(this, j["name"]);


	if (!j["prefab"].is_null() && j["prefab"].is_string()) {

		std::string cast = j["prefab"];

		json prefab = ResourceManager::getInstance()->getPrefabs()[cast];

		if (!prefab.is_null()) {
			prefab["name"] = j["name"];
			ent->init(prefab);

			if (!prefab["components"].is_null() && prefab["components"].is_array()) {
				std::vector<json> e = prefab["components"];
				for (json c : e) {
					ent->addComponentFromJson(c);
				}
			}
		}
	}

	ent->init(j);
	if (!j["components"].is_null() && j["components"].is_array()) {
		std::vector<json> e = j["components"];
		for (json c : e) {
			ent->addComponentFromJson(c);
		}
	}

	return ent;
}
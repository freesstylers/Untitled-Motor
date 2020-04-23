#include "Scene/Scene.h"

#include <functional>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
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
	MotorCasaPaco::getInstance()->getSM()->destroyAllCameras();
	for (std::pair<std::string, Entity*> i : entities) {
		delete i.second;
	}
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
			if (UI_Elem["type"] == "layout")
				MotorCasaPaco::getInstance()->getGUI_Manager()->loadLayout(UI_Elem["name"]);

			else if (UI_Elem["type"] == "entity")
			{
				entities[UI_Elem["name"]] = createEntity(UI_Elem);
			}
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
	addedEntitiesCounter=0;
}

void Scene::preupdate()
{
	auto i = entities.begin();
	while (i != entities.end()) {
		auto aux = i;
		aux++;
		if (!((*i).second)->getActive()) {
			delete (*i).second;
			entities.erase(i);
		}
		i = aux;
	}

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

Entity* Scene::addEntity(std::string name)
{
	Entity* ent;
	if (getEntity(name) != nullptr) {
		ent = new Entity(this, name + "_" + std::to_string(addedEntitiesCounter));
	}
	else ent = new Entity(this, name);
	entities[ent->getName()] = ent;
	addedEntitiesCounter++;
}

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
	std::map<std::string, Entity*> dontDelete;
	for (std::pair<std::string, Entity*> i : entities) {
		//Esto esta para que haya objetos que no se eliminen entre escenas
		//Principalmente para el gameManager o cualquier otro singleton
		if (!i.second->DontDestroyOnLoad)
			delete i.second;
		else
			dontDelete.insert(i);
	}
	entities.clear();

	//Volvemos a meter las entidades que no queremos eliminar
	for (std::pair<std::string, Entity*> i : dontDelete)
	{
		entities.insert(i);
	}
	dontDelete.clear();
}

void Scene::setupScene(json& j) {
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
			else
				entitiesWithoutParent_.push_back(entities[ent["name"]]);
		}
	}

	if (!j["UI"].is_null() && j["UI"].is_array()) {
		std::vector<json> e = j["UI"];

		for (json UI_Elem : e) {
			if (!UI_Elem["type"].is_null() && !UI_Elem["name"].is_null()) {

				bool visible = true;
				if (!UI_Elem["visible"].is_null())
					visible = UI_Elem["visible"];


				if (UI_Elem["type"] == "layout")
					MotorCasaPaco::getInstance()->getGUI_Manager()->loadLayout(UI_Elem["name"], visible);

				else if (UI_Elem["type"] == "entity")
				{
					entities[UI_Elem["name"]] = createEntity(UI_Elem);
					entitiesWithoutParent_.push_back(entities[UI_Elem["name"]]);
				}
			}
		}
	}
}

void Scene::recursivelyActivateEntities(Entity* ent) {
	ent->setEnabled(ent->isEnabled());

	auto children = ent->getChildren();

	std::map<std::string, Entity*>::iterator it = children.begin();
	while (it != children.end()) {
		recursivelyActivateEntities(it->second);
		it++;
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

std::list<Entity*> Scene::getEntitiesByTag(const std::string& tag)
{
	std::list<Entity*>* entityTags = new std::list<Entity*>();

	for (auto it : entities)
	{
		if (it.second->getTag() == tag)
		{
			entityTags->push_back(it.second);
		}
	}

	return *entityTags;
}

void Scene::start() {
	for (Entity* e : entitiesWithoutParent_)
		recursivelyActivateEntities(e);
	entitiesWithoutParent_.clear();

	addedEntitiesCounter = 0;
}

void Scene::preupdate()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->preupdate();
	}
}

void Scene::physicsUpdate()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->physicsUpdate();
	}
}

void Scene::update()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->update();
	}
}

void Scene::lateUpdate()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->lateUpdate();
	}
}

void Scene::pausedUpdate()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->pausedUpdate();
	}
}

void Scene::alwaysLateUpdate()
{
	for (pair<string, Entity*> e : entities) {
		if (e.second->isActive()) e.second->alwaysLateUpdate();
	}
}

void Scene::deleteInstances()
{
	for (auto it = executioner.begin(); it != executioner.end();)
	{
		auto aux = it;
		auto originalEntity = entities.find(it->first);
		aux++;
		//excluimos a los que no se deben eliminar (por si acaso)
		if (it->second->DontDestroyOnLoad) {
			it = aux;
			continue;
		}
		delete it->second;
		it->second = nullptr;
		executioner.erase(it);
		entities.erase(originalEntity);
		it = aux;
	}
}
Entity* Scene::createEntity(json& j)
{

	std::string tag = "Untagged";
	if (!j["tag"].is_null()) {
		std::string aux = j["tag"];
		tag = aux;
	}
	bool d = false;
	if (!j["dontDestroyOnLoad"].is_null()) {
		bool destroy = j["dontDestroyOnLoad"];
		d = destroy;
	}

	bool entEnabled = true;
	if (!j["enabled"].is_null() && j["enabled"] == "false")
		entEnabled = false;

	Entity* ent = new Entity(this, j["name"], tag, entEnabled);
	ent->DontDestroyOnLoad = d;

	if (!j["prefab"].is_null() && j["prefab"].is_string()) {

		std::string cast = j["prefab"];

		json prefab = ResourceManager::getInstance()->getPrefabs()[cast];

		if (!prefab.is_null()) {
			prefab["name"] = j["name"];

			if (tag == "Untagged" && !prefab["tag"].is_null())
				ent->setTag(prefab["tag"]);
			if (!prefab["dontDestroyOnLoad"].is_null())
				ent->DontDestroyOnLoad = prefab["dontDestroyOnLoad"];

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

Entity* Scene::addEntity(std::string name, std::string tag, bool callStart) {
	Entity* ent;
	if (getEntity(name) != nullptr) {
		ent = new Entity(this, name + "_" + std::to_string(addedEntitiesCounter), tag);
	}
	else ent = new Entity(this, name, tag);
	entities[ent->getName()] = ent;

	addedEntitiesCounter++;
	return ent;
}

bool Scene::deleteEntity(const std::string name) {
	auto it = entities.find(name);
	if (it != entities.end()) {
		executioner.insert(*it);
		return true;
	}

	return false;
}

string Scene::getName() const {
	return name;
}

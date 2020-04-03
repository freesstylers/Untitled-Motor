#include "Scene.h"

#include "Core.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include "ResourceManager.h"

#include <functional>

Scene::Scene()
{
}

Scene::~Scene()
{
	Core::getInstance()->getOgreWin()->removeAllViewports();
	//delete cam;
	entities.clear();
}

void Scene::setupScene(json& j)
{
	string interm = j["name"];
	name = interm;

	if (!j["entities"].is_null() && j["entities"].is_array()) {
		vector<json> e = j["entities"];
		for (json ent : e) {
			entities[ent["name"]] = createEntity(ent);
		}

		// Set the parents after all entities are loaded to avoid order problems
		for (json ent : e) {
			if (!ent["parent"].is_null())
				entities[ent["name"]]->setParent(ent["parent"]);
		}
	}

	Ogre::Light* luz = Core::getInstance()->getSM()->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);
}

//Ogre::Camera* Scene::getCam()
//{
//	return cam;
//}

//Ogre::Viewport* Scene::getVP()
//{
//	return vp;
//}

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
				vector<json> e = prefab["components"];
				for (json c : e) {
					ent->addComponentFromJson(c);
				}
			}
		}
	}

	ent->init(j);
	if (!j["components"].is_null() && j["components"].is_array()) {
		vector<json> e = j["components"];
		for (json c : e) {
			ent->addComponentFromJson(c);
		}
	}

	return ent;
}

//void Scene::createCam(json& j)
//{
//	int camNearClipDist = 1;
//	int camFarClipDist = 100000000;
//	bool autoAspectRatio = true;
//	Ogre::Vector3 camPos = Ogre::Vector3(100, 100, 100);
//	Ogre::Vector3 lookAt = Ogre::Vector3(0, 0, 0);
//	Ogre::ColourValue bgColour = Ogre::ColourValue(1, 1, 1, 1);
//
////this checks if there's an item for the camera in the json, and then checks if there's an item for each parameter
////this way, we can fill out only the parameters we want
//	if (!j["camera"].is_null()) {
//		if (!j["camera"]["nearClipDistance"].is_null())	camNearClipDist = j["camera"]["nearClipDistance"];
//		if (!j["camera"]["farClipDistance"].is_null())	camFarClipDist = j["camera"]["farClipDistance"];
//		if (!j["camera"]["autoAspectRatio"].is_null())	autoAspectRatio = j["camera"]["autoAspectRatio"];
//		if (!j["camera"]["pos"].is_null())
//		{
//			camPos.x = j["camera"]["pos"][0];
//			camPos.y = j["camera"]["pos"][1];
//			camPos.z = j["camera"]["pos"][2];
//		}
//		if (!j["camera"]["lookAt"].is_null())
//		{
//			lookAt.x = j["camera"]["lookAt"][0];
//			lookAt.y = j["camera"]["lookAt"][1];
//			lookAt.z = j["camera"]["lookAt"][2];
//		}
//		if (!j["camera"]["bgColor"].is_null())
//		{
//			bgColour.r = j["camera"]["bgColor"][0];
//			bgColour.g = j["camera"]["bgColor"][1];
//			bgColour.b = j["camera"]["bgColor"][2];
//			bgColour.a = j["camera"]["bgColor"][3];
//		}
//		else if (!j["camera"]["bgColour"].is_null())
//		{
//			bgColour.r = j["camera"]["bgColour"][0];
//			bgColour.g = j["camera"]["bgColour"][1];
//			bgColour.b = j["camera"]["bgColour"][2];
//			bgColour.a = j["camera"]["bgColour"][3];
//		}
//	}
//
//	// create the camera
//
//	cam = Core::getInstance()->getSM()->createCamera("cam");
//	cam->setNearClipDistance(camNearClipDist);
//	cam->setFarClipDistance(camFarClipDist);
//	cam->setAutoAspectRatio(autoAspectRatio);
//
//	Ogre::SceneNode* mCamNode = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode("nCam");
//	mCamNode->attachObject(cam);
//
//	mCamNode->setPosition(camPos);
//	mCamNode->lookAt(lookAt, Ogre::Node::TS_WORLD);
//
//	vp = Core::getInstance()->getOgreWin()->addViewport(cam);
//
//	vp->setBackgroundColour(bgColour);
//
//	cam->setAspectRatio(
//		Ogre::Real(vp->getActualWidth()) /
//		Ogre::Real(vp->getActualHeight()));
//}
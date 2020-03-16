#include "Scene.h"

#include "Core.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>

#include <functional>

Scene::Scene()
{
}

Scene::~Scene()
{
	Core::getInstance()->getOgreWin()->removeAllViewports();
	delete cam;
	entities.clear();
}

void Scene::setupScene(json& j)
{
	string interm = j["name"];
	name = interm;

	createCam(j);

	//load prefabs
	if (!j["entities"].is_null() && j["entities"].is_array()) {
		vector<json> e = j["entities"];
		for (json ent : e) {
			entities[ent["name"]] = createEntity(ent);
		}
	}

	Ogre::Entity* ogreEntity = Core::getInstance()->getSM()->createEntity("barrel.mesh");
	ogreEntity->setMaterialName("test");


	Ogre::SceneNode* Node = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode("test1");
	Node->attachObject(ogreEntity);
	Node->translate(10, 1, 10);

	Ogre::Entity* ogreEntity2 = Core::getInstance()->getSM()->createEntity("sphere.mesh");
	ogreEntity2->setMaterialName("sphereTest");


	Ogre::SceneNode* Node2 = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode("test2");
	Node2->attachObject(ogreEntity2);
	Node2->translate(0, 10, 0);
	Node2->scale(0.1, 0.1, 0.1);

	Ogre::Light* luz = Core::getInstance()->getSM()->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
}

Ogre::Camera* Scene::getCam()
{
	return cam;
}

Ogre::Viewport* Scene::getVP()
{
	return vp;
}

Entity* Scene::getEntity(const std::string& name)
{
	return entities[name];
}

Entity* Scene::createEntity(json& j)
{
	Entity* ent = new Entity(this, j["name"]);
	ent->init(j);
	if (!j["components"].is_null() && j["components"].is_array()) {
		vector<json> e = j["components"];
		for (json c : e) {
			ent->addComponentFromJson(c);
		}
	}
	

	return ent;
}

void Scene::createCam(json& j)
{
	int camNearClipDist = 1;
	int camFarClipDist = 100000000;
	bool autoAspectRatio = true;
	Ogre::Vector3 camPos = Ogre::Vector3(100, 100, 100);
	Ogre::Vector3 lookAt = Ogre::Vector3(0, 0, 0);
	Ogre::ColourValue bgColour = Ogre::ColourValue(1, 1, 1, 1);

//this checks if there's an item for the camera in the json, and then checks if there's an item for each parameter
//this way, we can fill out only the parameters we want
	if (!j["camera"].is_null()) {
		if (!j["camera"]["nearClipDistance"].is_null())	camNearClipDist = j["camera"]["nearClipDistance"];
		if (!j["camera"]["farClipDistance"].is_null())	camFarClipDist = j["camera"]["farClipDistance"];
		if (!j["camera"]["autoAspectRatio"].is_null())	autoAspectRatio = j["camera"]["autoAspectRatio"];
		if (!j["camera"]["pos"].is_null())
		{
			camPos.x = j["camera"]["pos"][0];
			camPos.y = j["camera"]["pos"][1];
			camPos.z = j["camera"]["pos"][2];
		}
		if (!j["camera"]["lookAt"].is_null())
		{
			lookAt.x = j["camera"]["lookAt"][0];
			lookAt.y = j["camera"]["lookAt"][1];
			lookAt.z = j["camera"]["lookAt"][2];
		}
		if (!j["camera"]["bgColor"].is_null())
		{
			bgColour.r = j["camera"]["bgColor"][0];
			bgColour.g = j["camera"]["bgColor"][1];
			bgColour.b = j["camera"]["bgColor"][2];
			bgColour.a = j["camera"]["bgColor"][3];
		}
		else if (!j["camera"]["bgColour"].is_null())
		{
			bgColour.r = j["camera"]["bgColour"][0];
			bgColour.g = j["camera"]["bgColour"][1];
			bgColour.b = j["camera"]["bgColour"][2];
			bgColour.a = j["camera"]["bgColour"][3];
		}
	}

	// create the camera

	cam = Core::getInstance()->getSM()->createCamera("cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(100000000);
	cam->setAutoAspectRatio(true);

	Ogre::SceneNode* mCamNode = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->translate(100, 100, 100);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	vp = Core::getInstance()->getOgreWin()->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}

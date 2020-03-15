#include "Scene.h"

#include "Core.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>

Scene::Scene()
{
	root = Core::getInstance()->getRoot();
	sm = Core::getInstance()->getSM();
	window = Core::getInstance()->getOgreWin();
}

Scene::~Scene()
{
	delete cam;
	delete vp;
	for (Entity* e : entities)
		delete e;
}

void Scene::setupScene(const json& j)
{
	// create the camera

	cam = sm->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(100000000);
	cam->setAutoAspectRatio(true);

	Ogre::SceneNode* mCamNode = sm->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->translate(100, 100, 100);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	vp = window->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));


	//call factories (one for entity and one for comps? Entity gets transform?
	//load prefabs
	//load components

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));

	Ogre::Entity* ogreEntity = sm->createEntity("barrel.mesh");
	ogreEntity->setMaterialName("test");


	Ogre::SceneNode* Node = sm->getRootSceneNode()->createChildSceneNode("test1");
	Node->attachObject(ogreEntity);
	Node->translate(10, 1, 10);

	Ogre::Entity* ogreEntity2 = sm->createEntity("sphere.mesh");
	ogreEntity2->setMaterialName("sphereTest");


	Ogre::SceneNode* Node2 = sm->getRootSceneNode()->createChildSceneNode("test2");
	Node2->attachObject(ogreEntity2);
	Node2->translate(0, 10, 0);
	Node2->scale(0.1, 0.1, 0.1);

	Ogre::Light* luz = sm->createLight("Luz");
	luz->setType(Ogre::Light::LT_POINT);
	luz->setDiffuseColour(0, 0, 0);

	Ogre::SceneNode* mLightNode = sm->getRootSceneNode()->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);
}

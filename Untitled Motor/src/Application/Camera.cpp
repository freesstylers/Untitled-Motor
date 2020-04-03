#include "Camera.h"
#include "Core.h"
#include "SceneManager.h"
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
#include "Transform.h"

Camera::Camera(json& args): Component(args)
{
	
}

Camera::~Camera()
{
	Component::~Component();
	Core::getInstance()->getOgreWin()->removeViewport(vp->getZOrder());
	delete vp;
	e_->getComponent<Transform>("Transform")->getNode()->removeAndDestroyChild(mCamNode->getName());
	delete mCamNode;
	delete cam;
}

bool Camera::ReceiveEvent(Event& event)
{
	return false;
}

void Camera::update()
{
	if (lookingAt) {
		Camera::lookAt(looking->getComponent<Transform>("Transform")->getNode()->getPosition());
	}
	if (following) {
		e_->getComponent<Transform>("Transform")->getNode()->setPosition(follow->getComponent<Transform>("Transform")->getNode()->getPosition() + vector);
	}
}

void Camera::init(json& j)
{
	int camNearClipDist = 1;
	int camFarClipDist = 100000000;
	bool autoAspectRatio = true;
	Ogre::Vector3 camPos = Ogre::Vector3(100, 100, 100);
	lookAtVec = Ogre::Vector3(0, 0, 0);
	Ogre::ColourValue bgColour = Ogre::ColourValue(1, 1, 1, 1);

	//this checks if there's an item for the camera in the json, and then checks if there's an item for each parameter
	//this way, we can fill out only the parameters we want
	if (!j["nearClipDistance"].is_null())	camNearClipDist = j["nearClipDistance"];
	if (!j["farClipDistance"].is_null())	camFarClipDist = j["farClipDistance"];
	if (!j["autoAspectRatio"].is_null())	autoAspectRatio = j["autoAspectRatio"];
	if (!j["lookingAt"].is_null()) {
		lookingAt = true;
		string name = j["lookingAt"];
		looking = SceneManager::getInstance()->getCurrentScene()->getEntity(name);
	}
	if (!j["lookAt"].is_null())
	{
		lookAtVec.x = j["lookAt"][0];
		lookAtVec.y = j["lookAt"][1];
		lookAtVec.z = j["lookAt"][2];
	}
	if (!j["bgColor"].is_null())
	{
		bgColour.r = j["bgColor"][0];
		bgColour.g = j["bgColor"][1];
		bgColour.b = j["bgColor"][2];
		bgColour.a = j["bgColor"][3];
	}
	else if (!j["bgColour"].is_null())
	{
		bgColour.r = j["bgColour"][0];
		bgColour.g = j["bgColour"][1];
		bgColour.b = j["bgColour"][2];
		bgColour.a = j["bgColour"][3];
	}

	//Get the Entity's position
	camPos = e_->getComponent<Transform>("Transform")->getPosition();

	if (!j["following"].is_null()) {
		following = true;
		string name = j["following"];
		follow = SceneManager::getInstance()->getCurrentScene()->getEntity(name);
		vector = camPos - follow->getComponent<Transform>("Transform")->getNode()->getPosition();
	}

	// create the camera
	cam = Core::getInstance()->getSM()->createCamera("cam");
	cam->setNearClipDistance(camNearClipDist);
	cam->setFarClipDistance(camFarClipDist);
	cam->setAutoAspectRatio(autoAspectRatio);

	//Create a child scene node for the camera
	mCamNode = e_->getComponent<Transform>("Transform")->getNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);
	mCamNode->setPosition(camPos);

	Camera::lookAt(lookAtVec);
	


	vp = Core::getInstance()->getOgreWin()->addViewport(cam);

	vp->setBackgroundColour(bgColour);

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}

void Camera::redefine(json& args)
{
	if (args["nearClipDistance"].is_null())
		args["nearClipDistance"] = cam->getNearClipDistance();

	if (args["farClipDistance"].is_null())
		args["farClipDistance"] = cam->getFarClipDistance();

	if (args["autoAspectRatio"].is_null())
		args["autoAspectRatio"] = cam->getAutoAspectRatio();

	if (args["lookingAt"].is_null() && lookingAt)
		args["lookingAt"] = looking->getName();

	if (args["lookAt"].is_null())
		args["lookAt"] = { lookAtVec.x, lookAtVec.y, lookAtVec.z };

	if (args["bgColor"].is_null() && args["bgColour"].is_null())
		args["bgColor"] = { vp->getBackgroundColour().r, vp->getBackgroundColour().g, vp->getBackgroundColour().b, vp->getBackgroundColour().a };

	if (args["following"].is_null() && following)
		args["following"] = follow->getName();


	Component::~Component();
	Core::getInstance()->getOgreWin()->removeViewport(vp->getZOrder());
	delete vp;
	e_->getComponent<Transform>("Transform")->getNode()->removeAndDestroyChild(mCamNode->getName());
	delete mCamNode;
	delete cam;

	vp = nullptr;
	cam = nullptr;
	mCamNode = nullptr;
	follow = nullptr;

	init(args);
}

//Coloca la direccion de la camara, sin girarla sobre su eje x, para que no "vuelque"
void Camera::lookAt(Ogre::Vector3 point)
{
	cam->lookAt(point);
}

Ogre::Camera* Camera::getCam()
{
	return cam;
}

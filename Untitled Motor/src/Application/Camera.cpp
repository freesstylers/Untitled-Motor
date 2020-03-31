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
	Ogre::Vector3 lookAt = Ogre::Vector3(0, 0, 0);
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
		lookAt.x = j["lookAt"][0];
		lookAt.y = j["lookAt"][1];
		lookAt.z = j["lookAt"][2];
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

	Camera::lookAt(lookAt);
	


	vp = Core::getInstance()->getOgreWin()->addViewport(cam);

	vp->setBackgroundColour(bgColour);

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
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

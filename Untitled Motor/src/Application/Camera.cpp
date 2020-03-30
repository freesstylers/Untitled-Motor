#include "Camera.h"
#include "Core.h"
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
	if (!j["camera"].is_null()) {
		if (!j["camera"]["nearClipDistance"].is_null())	camNearClipDist = j["camera"]["nearClipDistance"];
		if (!j["camera"]["farClipDistance"].is_null())	camFarClipDist = j["camera"]["farClipDistance"];
		if (!j["camera"]["autoAspectRatio"].is_null())	autoAspectRatio = j["camera"]["autoAspectRatio"];
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

	//Get the Entity's position
	camPos = e_->getComponent<Transform>("Transform")->getPosition();

	// create the camera

	cam = Core::getInstance()->getSM()->createCamera("cam");
	cam->setNearClipDistance(camNearClipDist);
	cam->setFarClipDistance(camFarClipDist);
	cam->setAutoAspectRatio(autoAspectRatio);

	//Create a child scene node for the camera
	Ogre::SceneNode* mCamNode = e_->getComponent<Transform>("Transform")->getNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(camPos);
	mCamNode->lookAt(lookAt, Ogre::Node::TS_WORLD);

	vp = Core::getInstance()->getOgreWin()->addViewport(cam);

	vp->setBackgroundColour(bgColour);

	cam->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}

#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Component.h"
#include <OgreCamera.h>

class Camera : public Component
{
public:
	Camera(json& args);
	~Camera();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

	void lookAt(Ogre::Vector3 point);
	Ogre::Camera* getCam();
private:
	bool lookingAt = false;
	bool following = false;

	Entity* looking = nullptr;

	Ogre::Vector3 vector;
	Entity* follow = nullptr;

	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	Ogre::SceneNode* mCamNode;
};


#endif //CAMERA_H
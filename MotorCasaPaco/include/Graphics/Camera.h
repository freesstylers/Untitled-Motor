#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/Component.h"

namespace Ogre {
	class Camera;
	class Entity;
	class SceneNode;
	class Viewport;
}

class Camera : public Component
{
public:
	Camera(json& args);
	~Camera();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;
	void redefine(json& args) override;

	void lookAt(Ogre::Vector3 point);
	Ogre::Camera* getCam();
private:
	bool lookingAt = false;
	bool following = false;

	Entity* looking = nullptr;

	Vector3 vector;
	Entity* follow = nullptr;

	Ogre::Camera* cam;
	Ogre::Viewport* vp;
	Ogre::SceneNode* mCamNode;

	Vector3 lookAtVec;
};


#endif //CAMERA_H
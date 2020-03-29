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

private:
	Ogre::Camera* cam;
	Ogre::Viewport* vp;
};


#endif //CAMERA_H

#pragma once
#include "Component.h"
#include "Ogre.h"

class SimpleMovement : public Component
{
public:

	SimpleMovement(json& args);
	virtual void start();
	virtual void update();
	~SimpleMovement();

	float speed;
	float rotateSpeed;

};


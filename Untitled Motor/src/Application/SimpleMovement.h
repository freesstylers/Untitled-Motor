#pragma once
#include "Component.h"

class SimpleMovement : public Component
{
public:

	SimpleMovement(json& args);
	virtual void start();
	virtual void update();
	void controllerMovement();
	void keyboardMovement();
	~SimpleMovement() {};

	float speed;
	float rotateSpeed;
	bool onlycontroller = false;

private:
	float deadZoneX;
	float deadZoneY;
	float deadZoneRange;

};


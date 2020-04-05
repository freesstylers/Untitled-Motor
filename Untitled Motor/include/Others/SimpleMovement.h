#pragma once
#include "Entity/Component.h"

class SimpleMovement : public Component
{
public:

	SimpleMovement(json& args);
	void init(json& args) override;
	void redefine(json& args) override;
	void start() override;
	void update() override;
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


#pragma once
#include "Component.h"
class ForcesTest : public Component
{
public:
	ForcesTest(json& args);
	virtual void start();
	virtual void update();
	~ForcesTest() {};

private:
	float deadZoneX;
	float deadZoneY;
	float deadZoneRange;
	float speed=20;
};


#pragma once
#include "Entity/Component.h"
class ForcesTest : public Component
{
public:
	ForcesTest(json& args);
	virtual void start();
	virtual void update();
	~ForcesTest() {};

private:
	float speed=20;
};


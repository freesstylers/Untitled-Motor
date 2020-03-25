#pragma once
#include "Component.h"
class MarbleMovementTest :public Component
{
public:
	MarbleMovementTest(json& args);
	bool ReceiveEvent(Event& event) override;
	virtual void update();
	~MarbleMovementTest();
private:
	float speed = 20;
};


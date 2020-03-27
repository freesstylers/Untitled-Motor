#pragma once
#include "Component.h"

class TestComponent : public Component
{
public:
	TestComponent(json& args);
	~TestComponent() override;
	bool ReceiveEvent(Event& event) override;
	void update() override;

	int value = 0;
};


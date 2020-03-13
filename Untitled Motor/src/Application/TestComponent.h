#pragma once
#include "Component.h"

class TestComponent : public Component
{
public:
	TestComponent(std::string n);
	bool ReceiveEvent(Event& event) override;
};


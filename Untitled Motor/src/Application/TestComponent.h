#pragma once
#include "Component.h"
#include "EventListener.h"

class TestComponent : public Component, public EventListener
{
public:
	TestComponent(std::string n);
	bool ReceiveEvent(Event& event) override;
};


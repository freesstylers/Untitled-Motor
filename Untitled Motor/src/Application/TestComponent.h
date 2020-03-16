#pragma once
#include "Component.h"
#include "EventListener.h"

class TestComponent :
	public Component, public EventListener
{
public:
	TestComponent(json& args);
	bool ReceiveEvent(Event& event) override;

	int value = 0;
};


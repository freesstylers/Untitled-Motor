#pragma once
#include "Component.h"
#include "EventListener.h"

class TestComponent :
	public Component, public EventListener
{
	bool ReceiveEvent(Event& event) override;
};


#pragma once
#include "Component.h"
#include "EventEmitter.h"

class TestComponent :
	public Component, public EventListener, public EventEmitter
{
	bool ReceiveEvent(Event& event) override;
};


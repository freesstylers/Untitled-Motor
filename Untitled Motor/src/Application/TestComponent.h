#pragma once
#include "Component.h"

class TestComponent : public Component
{
public:
	TestComponent(void* ent) :Component(ent) {};
	bool ReceiveEvent(Event& event) override;
};


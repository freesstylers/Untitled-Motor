#pragma once
#include "EventListener.h"

class Component: public EventListener
{
public:
	Component(void* ent);
protected:
	void* entity = nullptr;
};


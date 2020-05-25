#pragma once

#include "Events/Event.h"

class Entity;
class Component;

class EventListener
{
public:
	/**
	Receives the events emitted by the EventEmitters this listener is
	registered on.
	 */

	virtual ~EventListener();
	virtual bool ReceiveEvent(Event &event) = 0;
	virtual bool operator== (EventListener& o) = 0;
	virtual bool compare(Entity* e) = 0;
	virtual bool compare(Component* e) = 0;
};


#pragma once

#include "Events/Event.h"

class EventListener
{
public:
	/**
	Receives the events emitted by the EventEmitters this listener is
	registered on.
	 */
	virtual bool ReceiveEvent(Event &event) = 0;
};


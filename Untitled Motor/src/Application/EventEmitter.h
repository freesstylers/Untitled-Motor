#pragma once

#include "EventListener.h"
#include <vector>

class EventEmitter
{
public:
	/**
	 Propagates the given event among all listeners until one of them returns TRUE
	 */
	void EmitEvent(Event& event);

	/**
	 Registers a listener to receive the events emitted by this EventEmitter
	 */
	void RegisterListener(EventListener *listener);

	/**
	 Unregisters a listener to stop receiving the events emitted by this EventEmitter
	 It does NOT call its destructor nor deletes the instance.
	 */
	void UnregisterListener(EventListener* listener);

	/**
	 Unregisters ALL listeners to stop receiving the events emitted by this EventEmitter
	 It does NOT call their destructors nor deletes the instances.
	 */
	void ClearListeners();

private:
	std::vector<EventListener*> _listeners;
};

#pragma once

#include "Events/EventListener.h"
#include <vector>
#include <map>

class EventManager
{
public:

	static EventManager* getInstance();
	static bool setupInstance();
	static void clean();

	/**
	 Propagates the given event among all listeners until one of them returns TRUE
	 */
	void EmitEvent(Event& event);

	/**
	 Registers a listener to receive the events of the given type
	 */
	void RegisterListener(EventListener *listener, EventType eventType);

	/**
	 Unregisters a listener to stop receiving the events of the given type
	 It does NOT call its destructor nor deletes the instance.
	 */
	void UnregisterListener(EventListener* listener, EventType eventType);

	/**
	 Unregisters ALL listeners to stop receiving the events of the given type
	 It does NOT call their destructors nor deletes the instances.
	 */
	void ClearListeners(EventType type);

private:
	EventManager();
	~EventManager();
	static EventManager* instance;

	std::map<EventType, std::vector<EventListener*>> _listeners;
	
};

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
	 Creates a generic event using the given eventType
	 propagates it among all its listeners until one of them returns TRUE
	 */
	void EmitEvent(std::string eventType);

	/**
	 Registers a listener to receive the events of the given type
	 */
	void RegisterListener(EventListener *listener, std::string eventType);

	/**
	 Unregisters a listener to stop receiving the events of the given type
	 It does NOT call its destructor nor deletes the instance.
	 */
	void UnregisterListener(EventListener* listener, std::string eventType);

	/**
	Unregisters a listener to stop receiving any kind of event
	It does NOT call its destructor nor deletes the instance.
	*/
	void UnregisterListenerForAll(EventListener* listener);

	/**
	 Unregisters ALL listeners to stop receiving the events of the given type
	 It does NOT call their destructors nor deletes the instances.
	 */
	void ClearListeners(std::string type);

private:
	//Comprueba si hay un listener concreto para un evento, devuelve su posicion. -1 si no esta
	int hayListener(EventListener* listener, std::string eventType);

	EventManager();
	~EventManager();
	static EventManager* instance;

	std::map<std::string, std::vector<EventListener*>> _listeners;
	
};

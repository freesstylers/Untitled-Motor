#include "Events/EventManager.h"
#include "Entity/Entity.h"
#include <vector>
#include <algorithm>
#include "checkML.h"

using namespace std;

EventManager* EventManager::instance = 0;

EventManager* EventManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool EventManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new EventManager();
		return true;
	}

	return false;
}

void EventManager::clean()
{
	delete instance;
}

void EventManager::EmitEvent(Event& event)
{
	// Only emit the event if there are registered listeners for that event type
	map<std::string, vector<EventListener*>>::iterator it = _listeners.find(event.type);
	if (it != _listeners.end())
		for (EventListener* listener : it->second) {
			if (listener->ReceiveEvent(event))
				break;
		}
}

void EventManager::EmitEvent(std::string eventType) {
	Event e = Event(eventType);
	EmitEvent(e);
}


void EventManager::RegisterListener(EventListener* listener, std::string eventType)
{

	// Look for the EvenType on the map, insert it if it doesn't exist already
	map<std::string, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	if (it == _listeners.end())
		_listeners.insert(pair<std::string, vector<EventListener*>>(eventType, vector<EventListener*>({ listener })));

	// Only add the listener if it has not already been added before
	else if (hayListener(listener, eventType) == -1)
		it->second.push_back(listener);
}

void EventManager::UnregisterListener(EventListener* listener, std::string eventType)
{
	// Look for the EvenType on the map, and only then try to remove the listener
	map<std::string, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	if (it != _listeners.end()) {
		int n = hayListener(listener, eventType);
		it->second.erase(it->second.begin() + n);
	}
}

void EventManager::UnregisterListenerForAll(EventListener* listener)
{
	std::map<std::string, std::vector<EventListener*>>::iterator it = _listeners.begin();

	while (it != _listeners.end())
	{
		//Elimina segun la posicion
		int n = hayListener(listener, it->first);
		if (n != -1) {
			it->second.erase(it->second.begin() + n);
		}
		it++;
	}
}

void EventManager::ClearListeners(std::string eventType)
{
	// Look for the EvenType on the map, and only then try to clear all its listeners
	map<std::string, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	it->second.clear();
}

int EventManager::hayListener(EventListener* listener, std::string eventType)
{
	map<std::string, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	std::vector<EventListener*> v = it->second;
	int n = 0;
	for (EventListener* e : v) {
		if (*e == *listener) {
			break;
		}
		n++;
	}
	if (n < it->second.size())
		return n;
	return -1;
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	_listeners.clear();
}
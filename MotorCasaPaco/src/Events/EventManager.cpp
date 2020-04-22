#include "Events/EventManager.h"
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
	map<EventType, vector<EventListener*>>::iterator it = _listeners.find(event.type);
	if (it != _listeners.end())
		for (EventListener* listener : it->second) {
			if (listener->ReceiveEvent(event))
				break;
		}
}

void EventManager::RegisterListener(EventListener* listener, EventType eventType)
{
	// Look for the EvenType on the map, insert it if it doesn't exist already
	map<EventType, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	if (it == _listeners.end())
		_listeners.insert(pair<EventType, vector<EventListener*>>(eventType, vector<EventListener*>({ listener })));

	// Only add the listener if it has not already been added before
	else if (find(it->second.begin(), it->second.end(), listener) == it->second.end())
		it->second.push_back(listener);
}

void EventManager::UnregisterListener(EventListener* listener, EventType eventType)
{
	// Look for the EvenType on the map, and only then try to remove the listener
	map<EventType, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	if (it != _listeners.end())
		it->second.erase(std::remove(it->second.begin(), it->second.end(), listener), it->second.end());
}

void EventManager::UnregisterListenerForAll(EventListener* listener)
{
	for (auto foobar : _listeners)
		foobar.second.erase(std::remove(foobar.second.begin(), foobar.second.end(), listener), foobar.second.end());
}

void EventManager::ClearListeners(EventType eventType)
{
	// Look for the EvenType on the map, and only then try to clear all its listeners
	map<EventType, vector<EventListener*>>::iterator it = _listeners.find(eventType);
	it->second.clear();
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	_listeners.clear();
}
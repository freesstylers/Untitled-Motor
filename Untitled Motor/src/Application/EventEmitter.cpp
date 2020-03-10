#include "EventEmitter.h"
#include <vector>
#include <algorithm>

void EventEmitter::EmitEvent(Event& event)
{
	for (EventListener* listener : _listeners) {
		if (listener->ReceiveEvent(event))
			break;
	}
}

void EventEmitter::RegisterListener(EventListener* listener)
{
	_listeners.push_back(listener);
}

void EventEmitter::UnregisterListener(EventListener* listener)
{
	_listeners.erase(std::remove(_listeners.begin(), _listeners.end(), listener), _listeners.end());
}

void EventEmitter::ClearListeners()
{
	_listeners.clear();
}

#include "Events/EventListener.h"
#include "Events/EventManager.h"

EventListener::~EventListener()
{
	EventManager::getInstance()->UnregisterListenerForAll(this);
}

#include "TestComponent.h"

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.type == EventType::TEXT) {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

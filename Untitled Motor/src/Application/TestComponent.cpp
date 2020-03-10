#include "TestComponent.h"

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.id == EventID::Text) {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

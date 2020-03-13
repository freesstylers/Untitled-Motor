#include "TestComponent.h"

TestComponent::TestComponent(std::string n): Component(n) { }

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.type == EventType::TEXT) {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

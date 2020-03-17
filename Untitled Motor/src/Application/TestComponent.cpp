#include "TestComponent.h"
#include <iostream>

TestComponent::TestComponent(json& args): Component(args)
{
	value = args["value"];

	std::cout << args["type"] << ": " << args["tag"] << " " << value << "\n";
}

TestComponent::~TestComponent()
{
	Component::~Component();
}

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.type == EventType::TEXT) {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

#include "TestComponent.h"
#include <iostream>
#include "Entity/Entity.h"
#include "Entity/Transform.h"


TestComponent::TestComponent(json& args): Component(args)
{
	//std::cout << "Entity '" << getEntity()->getName() << "' constructor." << std::endl;
}

TestComponent::~TestComponent()
{
	Component::~Component();
}

void TestComponent::start()
{
	std::cout << "Entity '" << getEntity()->getName() << "' start." << std::endl;
}

void TestComponent::onActivated()
{
	std::cout << "Entity '" << getEntity()->getName() << "' onActivated." << std::endl;
}

void TestComponent::update() {
	Vector3 pos = getEntity()->getComponent<Transform>("Transform")->getWorldPosition();
	pos.X += 0.7f;
	getEntity()->getComponent<Transform>("Transform")->setWorldPosition(pos);
}

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.type == "TEXT") {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

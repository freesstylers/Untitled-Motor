#include "TestComponent.h"
#include <iostream>
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Input/InputManager.h"
#include "Scene/Scene.h"

TestComponent::TestComponent(json& args): Component(args)
{
	if (!args["refEntity"].is_null()) {
		std::string cast = args["refEntity"];
		refEntityName = cast;
	}

	std::cout << args["refEntity"] << std::endl;
}

TestComponent::~TestComponent()
{
	Component::~Component();
}

void TestComponent::start()
{
	std::cout << "Entity '" << getEntity()->getName() << "' start." << std::endl;

	refEntity = getEntity()->getScene()->getEntity(refEntityName);
}

void TestComponent::onActivated()
{
	std::cout << "Entity '" << getEntity()->getName() << "' onActivated." << std::endl;
}

void TestComponent::update() {
	Vector3 pos = getEntity()->getComponent<Transform>("Transform")->getWorldPosition();
	pos.X += 0.7f;
	getEntity()->getComponent<Transform>("Transform")->setWorldPosition(pos);

	if (refEntity != nullptr)
		refEntity->setEnabled(InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE));
}

bool TestComponent::ReceiveEvent(Event& event)
{
	if (event.type == "TEXT") {
		TextEvent textEvent = static_cast<TextEvent&>(event);
		printf(textEvent.text.c_str());
	}
	return false;
}

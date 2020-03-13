#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(std::string tag, PhysicsManager* manager):Component(tag)
{
	phManager = manager;
}

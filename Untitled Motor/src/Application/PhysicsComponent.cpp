#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(void* ent, PhysicsManager* manager):Component(ent)
{
	phManager = manager;
}

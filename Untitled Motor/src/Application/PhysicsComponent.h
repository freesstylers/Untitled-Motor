#pragma once
#include "Component.h"
#include "PhysicsManager.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(void* ent, PhysicsManager* manager);
protected:
	PhysicsManager* phManager = nullptr;
};
#pragma once
#include "Component.h"
#include "PhysicsManager.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(std::string tag, PhysicsManager* manager);
protected:
};
#pragma once
#include "PhysicsComponent.h"

class RigidBodyComponent : public PhysicsComponent
{
public:
	RigidBodyComponent(void* ent, PhysicsManager* manager);
protected:
	btRigidBody* body=nullptr;
};
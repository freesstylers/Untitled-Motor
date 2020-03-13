#pragma once
#include "PhysicsComponent.h"

class RigidBodyComponent : public PhysicsComponent
{
public:
	RigidBodyComponent(std::string tag, PhysicsManager* manager);
	btRigidBody* getRigidBody();
protected:
	btRigidBody* body=nullptr;
};
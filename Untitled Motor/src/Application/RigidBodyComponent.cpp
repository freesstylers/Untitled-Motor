#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(std::string tag, PhysicsManager* manager):PhysicsComponent(tag, manager)
{
}

btRigidBody* RigidBodyComponent::getRigidBody()
{
	return body;
}

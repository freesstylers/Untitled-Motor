#include "SphereBody.h"

SphereBody::SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user):RigidBodyComponent(tag, manager)
{
	body=phManager->addSphere(rad, initPos, mass);
	body->setUserPointer(user);
}


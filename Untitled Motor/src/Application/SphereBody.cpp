#include "SphereBody.h"

SphereBody::SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	body=phManager->addSphere(rad, initPos, mass);
	body->setUserPointer(user);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}


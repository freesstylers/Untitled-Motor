#include "SphereBody.h"

SphereBody::SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, int rbType):RigidBody(tag, manager, rbType)
{
	body=PhysicsManager::getInstance()->addSphere(rad, initPos, mass);
	body->setUserPointer(this);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}


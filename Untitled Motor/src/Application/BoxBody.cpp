#include "BoxBody.h"

BoxBody::BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, int rbType):RigidBody(tag, manager, rbType)
{
	body=PhysicsManager::getInstance()->addBox(initPos, dimensions, mass);
	body->setUserPointer(this);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}

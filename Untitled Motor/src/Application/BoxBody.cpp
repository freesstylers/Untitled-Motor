#include "BoxBody.h"

BoxBody::BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	body=phManager->addBox(initPos, dimensions, mass);
	body->setUserPointer(this);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}

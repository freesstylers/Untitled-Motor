#include "BoxBody.h"

BoxBody::BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, void* user, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	body=phManager->addBox(initPos, dimensions, mass);
	body->setUserPointer(user);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}

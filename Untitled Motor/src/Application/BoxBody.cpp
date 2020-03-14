#include "BoxBody.h"

BoxBody::BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, void* user, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	body=phManager->addBox(initPos, dimensions, mass);
	body->setUserPointer(user);
	if(rbTypeFlag==btCollisionObject::CF_STATIC_OBJECT || rbTypeFlag ==btCollisionObject::CF_KINEMATIC_OBJECT)//Por defecto os corpos son dinamicos
		body->setCollisionFlags(rbType);
}

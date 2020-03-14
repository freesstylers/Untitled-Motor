#include "SphereBody.h"

SphereBody::SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	body=phManager->addSphere(rad, initPos, mass);
	body->setUserPointer(user);
	if (rbTypeFlag == btCollisionObject::CF_STATIC_OBJECT || rbTypeFlag == btCollisionObject::CF_KINEMATIC_OBJECT)//Por d	efecto os corpos son dinamicos
		body->setCollisionFlags(rbType);
}


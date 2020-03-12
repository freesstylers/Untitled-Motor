#include "SphereBody.h"

SphereBody::SphereBody(void* ent, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user):RigidBodyComponent(ent, manager)
{
	body=phManager->addSphere(rad, initPos, mass);
	body->setUserPointer(user);
}

bool SphereBody::ReceiveEvent(Event& event)
{
	return false;
}

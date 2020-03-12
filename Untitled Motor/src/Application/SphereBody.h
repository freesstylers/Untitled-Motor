#pragma once
#include "RigidBodyComponent.h"


class SphereBody : public RigidBodyComponent
{
public:
	SphereBody(void* ent, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user);
	bool ReceiveEvent(Event& event) override;
};
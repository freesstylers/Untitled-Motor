#pragma once
#include "RigidBodyComponent.h"


class SphereBody : public RigidBodyComponent
{
public:
	SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, void* user, int rbType=0);
};
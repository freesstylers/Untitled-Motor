#pragma once
#include "RigidBody.h"


class SphereBody : public RigidBody
{
public:
	SphereBody(std::string tag, PhysicsManager* manager, float rad, btVector3 initPos, float mass, int rbType=0);
};
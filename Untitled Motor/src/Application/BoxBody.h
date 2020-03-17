#pragma once
#include "RigidBody.h"


class BoxBody : public RigidBody
{
public:
	BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, int rbType=0);
};
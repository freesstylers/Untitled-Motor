#pragma once
#include "RigidBodyComponent.h"


class BoxBody : public RigidBodyComponent
{
public:
	BoxBody(std::string tag, PhysicsManager* manager, btVector3 initPos, btVector3 dimensions, float mass, void* user, int rbType=0);
};
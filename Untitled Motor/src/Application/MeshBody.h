#pragma once
#include "RigidBody.h"


class MeshBody : public RigidBody
{
public:
	MeshBody(std::string tag, PhysicsManager* manager, btVector3 initPos, float mass, void* user, int rbType=0);
};
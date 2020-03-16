#pragma once
#include "RigidBodyComponent.h"


class MeshBody : public RigidBodyComponent
{
public:
	MeshBody(std::string tag, PhysicsManager* manager, btVector3 initPos, float mass, void* user, int rbType=0);
};
#pragma once
#include "PhysicsComponent.h"


class RigidBodyComponent : public PhysicsComponent
{
public:
	RigidBodyComponent(std::string tag, PhysicsManager* manager, int rbType);
	virtual void init();
	virtual void OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2);
	btRigidBody* getRigidBody();
protected:
	btRigidBody* body = nullptr;
	int rbTypeFlag;
};
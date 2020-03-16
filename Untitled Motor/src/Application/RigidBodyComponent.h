#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"

class RigidBodyComponent : public PhysicsComponent
{
public:
	RigidBodyComponent(std::string tag, PhysicsManager* manager, int rbType);
	virtual void init();
	virtual void preupdate();
	virtual void update();
	virtual void OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2);
	btRigidBody* getRigidBody();
protected:
	btRigidBody* body = nullptr;
	int rbTypeFlag;
private:
	TransformComponent auxTrans= TransformComponent("aux");
};
#pragma once
#include "PhysicsComponent.h"
#include "EventListener.h"
#include "EventManager.h"

class RigidBodyComponent : public PhysicsComponent, public EventListener
{
public:
	RigidBodyComponent(std::string tag, PhysicsManager* manager, int rbType);
	virtual void init();
	btRigidBody* getRigidBody();
protected:
	btRigidBody* body = nullptr;
	int rbTypeFlag;
};
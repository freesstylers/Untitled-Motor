#pragma once
#include "Component.h"
#include "Transform.h"
#include "EventListener.h"

class RigidBody :
	public Component, public EventListener
{
public:
	RigidBody(json& args);
	~RigidBody() override;

	virtual void init();
	virtual void preupdate();
	virtual void update();
	virtual void OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2);
	btRigidBody* getRigidBody();

	bool getUpdatecheck();

protected:

	btRigidBody* body = nullptr;
	int rbTypeFlag;

private:

	Ogre::Vector3 bakPosition;
	Ogre::Vector3 bakScale;
	Ogre::Quaternion bakRotation;

	bool updatecheck = false;
};
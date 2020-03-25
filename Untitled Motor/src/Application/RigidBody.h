#pragma once
#include "Component.h"
#include "Ogre.h"

class RigidBody :
	public Component
{
public:
	RigidBody(json& args);
	~RigidBody() override;

	void init(json& args) override;
	void preupdate() override;
	void update() override;
	virtual void OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2);
	btRigidBody* getRigidBody();
	void createRigidBody(json& args);
	bool ReceiveEvent(Event& event)override;

	bool isRBStatic();
	bool isRBKinematic();

protected:

	btRigidBody* body = nullptr;
	int rbTypeFlag;

private:
	bool isStatic = false;
	bool isKinematic = false;

	Ogre::Vector3 bakPosition;
	Ogre::Vector3 bakScale;
	Ogre::Quaternion bakRotation;
};
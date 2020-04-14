#pragma once
#include "Entity/Component.h"
#include "Ogre.h"

class btManifoldPoint;
enum ForceType {
	CENTRAL_IMPULSE,
	CENTRAL_FORCE,
	FORCE,
	IMPULSE,
	PUSH_IMPULSE,
	TORQUE,
	TORQUE_IMPULSE,
	TORQUE_TURN_IMPULSE,
	LINEAR_VELOCITY,
	ANGULAR_VELOCITY
};

class RigidBody :
	public Component
{
public:
	RigidBody(json& args);
	~RigidBody() override;

	void init(json& args) override;
	void redefine(json& args) override;
	void preupdate() override;
	void physicsUpdate() override;
	virtual void OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2);
	btRigidBody* getRigidBody();
	void applyForce(ForceType type, Vector3 force, Vector3 relPos = Vector3(0,0,0));


	void createRigidBody(json& args);

	bool isRBStatic();
	bool isRBKinematic();

protected:

	btRigidBody* body = nullptr;
	int rbTypeFlag;

private:
	bool isStatic = false;
	bool isKinematic = false;

	Vector3 bakPosition;
	Vector3 bakScale;
	Quaternion bakRotation;
	std::string shape;
};
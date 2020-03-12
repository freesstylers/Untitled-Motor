#pragma once
#include <btBulletDynamicsCommon.h>
#include <vector>

class PhysicsManager
{
public:
	PhysicsManager();
	void initWorld();
	void stepWorld();
	void addRigidBody(btRigidBody* body);
	btRigidBody* addSphere(float rad, btVector3 pos, float mass);
	btRigidBody* addBox(btVector3 pos, btVector3 dimensions, float mass);
	std::vector<btRigidBody*> getBodies();

	~PhysicsManager();
private:
	btDynamicsWorld* world=nullptr;
	btCollisionConfiguration* config=nullptr;
	btDispatcher* dispatcher=nullptr;
	btBroadphaseInterface* broadphase=nullptr;
	btConstraintSolver* solver=nullptr;

	std::vector<btRigidBody*> bodies;
};


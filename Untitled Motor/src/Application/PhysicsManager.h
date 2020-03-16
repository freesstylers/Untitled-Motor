#pragma once
#include <btBulletDynamicsCommon.h>
#include <vector>

class PhysicsManager
{
public:
	~PhysicsManager();

	static PhysicsManager* getInstance();
	static bool setupInstance();
	static void clean();

	void initWorld();
	void stepWorld();
	void addRigidBody(btRigidBody* body);
	btRigidBody* addSphere(float rad, btVector3 pos, float mass);
	btRigidBody* addBox(btVector3 pos, btVector3 dimensions, float mass);
	std::vector<btRigidBody*> getBodies();

private:
	PhysicsManager();

	btDynamicsWorld* world=nullptr;
	btCollisionConfiguration* config=nullptr;
	btDispatcher* dispatcher=nullptr;
	btBroadphaseInterface* broadphase=nullptr;
	btConstraintSolver* solver=nullptr;

	static PhysicsManager* instance;
	
	std::vector<btRigidBody*> bodies;
};


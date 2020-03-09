#pragma once
#include <btBulletDynamicsCommon.h>
#include <map>

class PhysicsManager
{
public:
	PhysicsManager();
	void initWorld();
	void stepWorld();
	void addRigidBody(std::string id, btRigidBody* body);
	btRigidBody* addSphere(std::string id, float rad, btVector3 pos, float mass);
	btRigidBody* addBox(std::string id, btVector3 pos, btVector3 dimensions, float mass);
	std::map<std::string, btRigidBody*> getBodies();

	~PhysicsManager();
private:
	btDynamicsWorld* world=nullptr;
	btCollisionConfiguration* config=nullptr;
	btDispatcher* dispatcher=nullptr;
	btBroadphaseInterface* broadphase=nullptr;
	btConstraintSolver* solver=nullptr;

	std::map<std::string, btRigidBody*> bodies;
};


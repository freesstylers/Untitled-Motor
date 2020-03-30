#pragma once
#include <btBulletDynamicsCommon.h>
#include <OgreMesh.h>
#include <vector>

class PhysicsManager
{
public:
	~PhysicsManager();

	static PhysicsManager* getInstance();
	static bool setupInstance();
	static void clean();

	btDynamicsWorld* getWorld();

	void initWorld();
	void stepWorld(float time);
	void addRigidBody(btRigidBody* body);

	btRigidBody* createRigidBody(const std::string& shape, const btVector3& pos, Ogre::Entity* ent, const float& mass, const bool& isAnimated);
	btRigidBody* createRigidBody(const std::string& shape, const Ogre::Vector3& pos, Ogre::Entity* ent, const float& mass, const bool& isAnimated);

private:
	PhysicsManager();

	btDynamicsWorld* world=nullptr;
	btCollisionConfiguration* config=nullptr;
	btDispatcher* dispatcher=nullptr;
	btBroadphaseInterface* broadphase=nullptr;
	btConstraintSolver* solver=nullptr;

	static PhysicsManager* instance;
};


#pragma once
#include <vector>
#include "Others/General.h"

namespace Ogre {
	class Entity;
}

class btRigidBody;
class btDynamicsWorld;
class btCollisionConfiguration;
class btDispatcher;
class btBroadphaseInterface;
class btConstraintSolver;

class PhysicsManager
{
public:

	static PhysicsManager* getInstance();
	static bool setupInstance();
	static void clean();

	btDynamicsWorld* getWorld();

	void initWorld();
	void stepWorld();
	void addRigidBody(btRigidBody* body);
	void setActive(bool active);

	btRigidBody* createRigidBody(const std::string& shape, const Vector3& pos, Ogre::Entity* ent, const float& mass, const bool& isAnimated, const bool& addToWorld = true);

private:
	PhysicsManager();
	~PhysicsManager();

	bool active_ = true;

	btDynamicsWorld* world=nullptr;
	btCollisionConfiguration* config=nullptr;
	btDispatcher* dispatcher=nullptr;
	btBroadphaseInterface* broadphase=nullptr;
	btConstraintSolver* solver=nullptr;

	static PhysicsManager* instance;
};


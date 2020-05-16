#include "Physics/PhysicsManager.h"

#include <BtOgreGP.h>
#include <BtOgreExtras.h>
#include <BtOgrePG.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <btBulletDynamicsCommon.h>
#include <OgreMesh.h>
#include "MotorCasaPaco.h"

PhysicsManager* PhysicsManager::instance = 0;

PhysicsManager::PhysicsManager()
{
	config = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(config);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);

	STEP_TIME = 1.0f / ITERATIONS_PER_SECOND;
}

void PhysicsManager::initWorld()
{
	world->setGravity(btVector3(0, -100, 0));
}

void PhysicsManager::stepWorld()
{
	if (!active_)
		return;

	world->stepSimulation(MotorCasaPaco::getInstance()->DeltaTime(), 1, STEP_TIME);
}

void PhysicsManager::addRigidBody(btRigidBody* body)
{
	world->addRigidBody(body);
}

void PhysicsManager::setActive(bool active)
{
	this->active_ = active;
}

void PhysicsManager::setIterationsPerSecond(int iterationsPerSecond)
{
	ITERATIONS_PER_SECOND = iterationsPerSecond;
	STEP_TIME = 1.0f / ITERATIONS_PER_SECOND;
}

void PhysicsManager::setGravity(Vector3 gravity)
{
	world->setGravity(gravity);
}

void PhysicsManager::setDefaultSleepingThresholds(float linear, float angular)
{
	DEFAULT_LINEAR_SLEEPING_THRESHOLD = linear;
	DEFAULT_ANGULAR_SLEEPING_THRESHOLD = angular;
}

btRigidBody* PhysicsManager::createRigidBody(const std::string& shape, const Vector3& pos, Ogre::Entity* ent, const float& mass, const bool& isAnimated, const bool& addToWorld)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(pos);
	btVector3 inertia(0, 0, 0);
	btCollisionShape* colShape;

	if (isAnimated) {
		BtOgre::AnimatedMeshToShapeConverter convert = BtOgre::AnimatedMeshToShapeConverter(ent);
		if (shape == "cube") {
			colShape = convert.createBox();
		}
		else if (shape == "sphere") {
			colShape = convert.createSphere();
		}
		else if (shape == "capsule") {
			colShape = convert.createCapsule();
		}
		else if (shape == "cylinder") {
			colShape = convert.createCylinder();
		}
		else {
			colShape = convert.createConvex();
		}
	}
	else {
		BtOgre::StaticMeshToShapeConverter convert = BtOgre::StaticMeshToShapeConverter(ent);
		if (shape == "cube") {
			colShape = convert.createBox();
		}
		else if (shape == "sphere") {
			colShape = convert.createSphere();
		}
		else if (shape == "capsule") {
			colShape = convert.createCapsule();
		}
		else if (shape == "cylinder") {
			colShape = convert.createCylinder();
		}
		else {
			colShape = convert.createConvex();
		}
	}

	if (mass != 0.0)
		colShape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, colShape, inertia);
	btRigidBody* body = new btRigidBody(info);
	body->setSleepingThresholds(DEFAULT_LINEAR_SLEEPING_THRESHOLD, DEFAULT_ANGULAR_SLEEPING_THRESHOLD);
	
	if (addToWorld)
		addRigidBody(body);
	
	return body;
}

PhysicsManager::~PhysicsManager()
{
	delete world;
	delete config;
	delete solver;
	delete dispatcher;
	delete broadphase;
}

PhysicsManager* PhysicsManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool PhysicsManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new PhysicsManager();
		return true;
	}

	return false;
}

void PhysicsManager::clean()
{
	delete instance;
}

btDynamicsWorld* PhysicsManager::getWorld()
{
	return world;
}



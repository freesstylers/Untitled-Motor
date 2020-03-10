#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	config = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(config);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);
}

void PhysicsManager::initWorld()
{
	world->setGravity(btVector3(0, -10, 0));
}

void PhysicsManager::stepWorld()
{
	world->stepSimulation(1.0 / 60.0);
}

void PhysicsManager::addRigidBody(std::string id, btRigidBody* body)
{
	bodies[id] = body;
	world->addRigidBody(body);
}

btRigidBody* PhysicsManager::addSphere(std::string id, float rad, btVector3 pos, float mass)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(pos);
	btSphereShape* sphere = new btSphereShape(rad);
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		sphere->calculateLocalInertia(mass, inertia);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere);
	btRigidBody* body = new btRigidBody(info);
	addRigidBody(id, body);
	return body;
}

btRigidBody* PhysicsManager::addBox(std::string id, btVector3 pos, btVector3 dimensions, float mass)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(pos);
	btBoxShape* box = new btBoxShape(dimensions);
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0)
		box->calculateLocalInertia(mass, inertia);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, box);
	btRigidBody* body = new btRigidBody(info);
	addRigidBody(id, body);
	return body;
}

std::map<std::string, btRigidBody*> PhysicsManager::getBodies()
{
	return bodies;
}

PhysicsManager::~PhysicsManager()
{
	for (auto b : bodies) {
		world->removeRigidBody(b.second);
		delete b.second;
	}
	delete config;
	delete solver;
	delete dispatcher;
	delete broadphase;
	delete world;
}



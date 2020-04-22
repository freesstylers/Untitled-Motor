#include "Physics/PhysicsManager.h"
#include "Physics/MeshStrider.h"

#include <BtOgreGP.h>
#include <BtOgreExtras.h>
#include <BtOgrePG.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <btBulletDynamicsCommon.h>
#include <OgreMesh.h>

PhysicsManager* PhysicsManager::instance = 0;

PhysicsManager::PhysicsManager()
{
	config = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* interm = new btCollisionDispatcher(config);
	btGImpactCollisionAlgorithm::registerAlgorithm(interm);
	dispatcher = interm;
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
	world->stepSimulation(1.0 / 60.0, 10);
}

void PhysicsManager::addRigidBody(btRigidBody* body)
{
	world->addRigidBody(body);
}

btRigidBody* PhysicsManager::createRigidBody(const std::string& shape, const Vector3& pos, Ogre::Entity* ent, const float& mass, const bool& isAnimated)
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
			MeshStrider* aux = new MeshStrider(ent->getMesh().getPointer());
			btGImpactMeshShape* interm = new btGImpactMeshShape(aux);
			interm->updateBound();

			colShape = interm;
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
			MeshStrider* aux = new MeshStrider(ent->getMesh().getPointer());
			btGImpactMeshShape* interm = new btGImpactMeshShape(aux);
			interm->updateBound();

			colShape = interm;
		}
	}

	if (mass != 0.0)
		colShape->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, colShape, inertia);
	btRigidBody* body = new btRigidBody(info);
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



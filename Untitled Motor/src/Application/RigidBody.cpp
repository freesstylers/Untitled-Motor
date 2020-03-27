#include "RigidBody.h"

#include "Entity.h"
#include "Mesh.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include <BtOgreExtras.h>

RigidBody::RigidBody(json& args) : Component(args)
{
}

RigidBody::~RigidBody()
{
	Component::~Component();
	PhysicsManager::getInstance()->getWorld()->removeRigidBody(body);
	delete body->getCollisionShape();
	delete body;
}

void RigidBody::init(json& args)//mandar unha mesaxe a outros componentes (por exemplo render) mandando informacion do corpo rixido
{
	createRigidBody(args);

	RigidBodyInfoEvent event(body);
	EventManager::getInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_INFO); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::getInstance()->EmitEvent(event);
	EventManager::getInstance()->ClearListeners(event.type);
}

void RigidBody::preupdate()
{
	//asigna o rigidbody a posicion e rotacion que manda o transform
	
	Transform* tr = getEntity()->getComponent<Transform>("Transform");

	bakPosition = tr->getWorldPosition();
	bakRotation = tr->getWorldRotation();
	bakScale = tr->getWorldScale();
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	trans.setOrigin(BtOgre::Convert::toBullet(tr->getWorldPosition()));
	trans.setRotation(BtOgre::Convert::toBullet(tr->getWorldRotation()));
	body->getMotionState()->setWorldTransform(trans);
	body->setWorldTransform(trans);

	body->getCollisionShape()->setLocalScaling(BtOgre::Convert::toBullet(bakScale));
	PhysicsManager::getInstance()->getWorld()->updateSingleAabb(body);
}

void RigidBody::physicsUpdate()
{
	//trala actualizacion das fisicas, o rigidbody volve a mandar sobre o transform
	Transform* tr = getEntity()->getComponent<Transform>("Transform");
	btTransform trans;
	trans = body->getWorldTransform();

	tr->setWorldPosition(BtOgre::Convert::toOgre(trans.getOrigin()));
	tr->setWorldRotation(BtOgre::Convert::toOgre(trans.getRotation()));
	tr->setScale(BtOgre::Convert::toOgre(body->getCollisionShape()->getLocalScaling()));
}

void RigidBody::OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2)
{
	RigidBodyCollisionEvent event(obj1, obj2);
	EventManager::getInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_COLLISION); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::getInstance()->EmitEvent(event);
}

btRigidBody* RigidBody::getRigidBody()
{
	return body;
}

void RigidBody::createRigidBody(json& args)
{
	//default rigidbody shape is mesh
	std::string shape = "mesh";
	float mass = 0.0;

	if (!args["shape"].is_null()) {
		std::string cast = args["shape"];
		shape = cast;
	}

	if (!args["mass"].is_null()) {
		//if it's kinematic or static, it won't have mass
		if ((args["isStatic"].is_null() || !args["isStatic"]) || (args["isKinematic"].is_null() || !args["isKinematic"]))
		{
			float cast = args["mass"];
			mass = cast;
		}
	}

	body = PhysicsManager::getInstance()->createRigidBody(shape, e_->getComponent<Transform>("Transform")->getPosition(), e_->getComponent<Mesh>("Mesh")->getOgreEntity(), mass, e_->getComponent<Mesh>("Mesh")->isMeshAnimated());

	body->setUserPointer(e_->getComponent<Transform>("Transform")->getNode());

	if (!args["isStatic"].is_null() && args["isStatic"])
	{
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
		isStatic = true;
	}
	else if(!args["isKinematic"].is_null() && args["isKinematic"])
	{
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		isKinematic = true;
	}
	else {
		body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
	}
}

bool RigidBody::isRBStatic()
{
	return isStatic;
}

bool RigidBody::isRBKinematic()
{
	return isKinematic;
}

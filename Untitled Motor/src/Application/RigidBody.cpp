#include "RigidBody.h"

#include "Entity.h"
#include "PhysicsManager.h"

RigidBody::RigidBody(json& args) : Component(args)
{
	//create body
}

RigidBody::~RigidBody()
{
}

void RigidBody::init()//mandar unha mesaxe a outros componentes (por exemplo render) mandando informacion do corpo rixido
{
	RigidBodyInfoEvent event(body);
	EventManager::GetInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_INFO); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::GetInstance()->EmitEvent(event);
	EventManager::GetInstance()->ClearListeners(event.type);
}

void RigidBody::preupdate()
{
	//asigna o rigidbody a posicion e rotacion que manda o transform
	
	Transform* tr = getEntity()->getComponent<Transform>("Transform");

	bakPosition = tr->getWorldPosition();
	bakRotation = tr->getWorldRotation();
	bakScale = tr->getWorldScale();

	btTransform trans;
	trans.setOrigin(btVector3(tr->getWorldPosition().x, tr->getWorldPosition().y, tr->getWorldPosition().z));
	trans.setRotation(btQuaternion(tr->getWorldRotation().x, tr->getWorldRotation().y, tr->getWorldRotation().z, tr->getWorldRotation().w));
	body->getMotionState()->setWorldTransform(trans);

	body->getCollisionShape()->setLocalScaling(btVector3(bakScale.x, bakScale.y, bakScale.z));
}

void RigidBody::update()
{
	//trala actualizacion das fisicas, o rigidbody volve a mandar sobre o transform
	Transform* tr = getEntity()->getComponent<Transform>("transform");
	btTransform trans;
	if (tr->getWorldPosition() != bakPosition || tr->getWorldRotation() != bakRotation || tr->getWorldScale() != bakScale) {//se se modificou o transform despois do step cambiase o corpo a onde manda o tranform
		trans.setOrigin(btVector3(tr->getWorldPosition().x, tr->getWorldPosition().y, tr->getWorldPosition().z));
		trans.setRotation(btQuaternion(tr->getWorldRotation().x, tr->getWorldRotation().y, tr->getWorldRotation().z, tr->getWorldRotation().w));
		body->getMotionState()->setWorldTransform(trans);

		PhysicsManager::getInstance()->getWorld()->updateSingleAabb(body);
	}
	else {//se non se modificou o transform actualizase cos valores do corpo rixido
		body->getMotionState()->getWorldTransform(trans);
		tr->setWorldPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		tr->setWorldRotation(Ogre::Quaternion(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ()));
		tr->setScale(Ogre::Vector3(body->getCollisionShape()->getLocalScaling().x, body->getCollisionShape()->getLocalScaling().y, body->getCollisionShape()->getLocalScaling().z));
	}
}

void RigidBody::OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2)
{
	RigidBodyCollisionEvent event(obj1, obj2);
	EventManager::GetInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_COLLISION); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::GetInstance()->EmitEvent(event);
}

btRigidBody* RigidBody::getRigidBody()
{
	return body;
}


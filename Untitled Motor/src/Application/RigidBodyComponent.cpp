#include "RigidBodyComponent.h"
#include "Entity.h"

RigidBodyComponent::RigidBodyComponent(std::string tag, PhysicsManager* manager, int rbType):PhysicsComponent(tag, manager)
{
	rbTypeFlag = rbType;
}

void RigidBodyComponent::init()//mandar unha mesaxe a outros componentes (por exemplo render) mandando informacion do corpo rixido
{
	RigidBodyInfoEvent event(body);
	EventManager::GetInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_INFO); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::GetInstance()->EmitEvent(event);
	EventManager::GetInstance()->ClearListeners(event.type);
}

void RigidBodyComponent::preupdate()
{
	//asigna o rigidbody a posicion e rotacion que manda o transform
	
	TransformComponent* tr=getEntity()->getComponent<TransformComponent>("transform");
	auxTrans = *tr;
	btTransform trans;
	trans.setOrigin(btVector3(tr->getPosition().x, tr->getPosition().y, tr->getPosition().z));
	trans.setRotation(btQuaternion(tr->getRotation().x, tr->getRotation().y, tr->getRotation().z, tr->getRotation().w));
	body->getMotionState()->setWorldTransform(trans);
}

void RigidBodyComponent::update()
{
	//trala actualizacion das fisicas, o rigidbody volve a mandar sobre o transform
	TransformComponent* tr = getEntity()->getComponent<TransformComponent>("transform");
	btTransform trans;
	if (tr->getPosition() != auxTrans.getPosition() || tr->getRotation() != auxTrans.getRotation() || tr->getScale() != auxTrans.getScale()) {//se se modificou o transform despois do step cambiase o corpo a onde manda o tranform
		trans.setOrigin(btVector3(tr->getPosition().x, tr->getPosition().y, tr->getPosition().z));
		trans.setRotation(btQuaternion(tr->getRotation().x, tr->getRotation().y, tr->getRotation().z, tr->getRotation().w));
		body->getMotionState()->setWorldTransform(trans);
	}
	else {//se non se modificou o transform actualizase cos valores do corpo rixido
		body->getMotionState()->getWorldTransform(trans);
		tr->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		tr->setRotation(Ogre::Quaternion(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ()));
	}
}

void RigidBodyComponent::OnCollisionEnter(btManifoldPoint& cp, const btCollisionObject* obj1, const btCollisionObject* obj2)
{
	RigidBodyCollisionEvent event(obj1, obj2);
	EventManager::GetInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_COLLISION); //rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::GetInstance()->EmitEvent(event);
}

btRigidBody* RigidBodyComponent::getRigidBody()
{
	return body;
}

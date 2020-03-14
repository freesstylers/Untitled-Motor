#include "RigidBodyComponent.h"

RigidBodyComponent::RigidBodyComponent(std::string tag, PhysicsManager* manager, int rbType):PhysicsComponent(tag, manager)
{
	rbTypeFlag = rbType;
}

void RigidBodyComponent::init()//mandar unha mesaxe a outros componentes (por exemplo render) mandando informacion do corpo rixido
{
	RigidBodyInfoEvent event(body);
	//EventManager::GetInstance()->RegisterListener(entity, EventType::RIGIDBODY_INFO); rexistrar a entidade que alberga o componente para mandalo mesaxe os demais componentes desta
	EventManager::GetInstance()->EmitEvent(event);
}

btRigidBody* RigidBodyComponent::getRigidBody()
{
	return body;
}

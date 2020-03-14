#include "MeshBody.h"

MeshBody::MeshBody(std::string tag, PhysicsManager* manager, btVector3 initPos, float mass, void* user, int rbType):RigidBodyComponent(tag, manager, rbType)
{
	//Colle os puntos dun arquivo de malla e os utiliza para crear a xeometria das colisions do corpo rixido
	body->setUserPointer(user);
	if (rbTypeFlag == btCollisionObject::CF_STATIC_OBJECT || rbTypeFlag == btCollisionObject::CF_KINEMATIC_OBJECT)//Por defecto os corpos son dinamicos
		body->setCollisionFlags(rbType);
}

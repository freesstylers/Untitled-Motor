#include "MeshBody.h"

MeshBody::MeshBody(std::string tag, PhysicsManager* manager, btVector3 initPos, float mass, void* user, int rbType):RigidBody(tag, manager, rbType)
{
	//Colle os puntos dun arquivo de malla e os utiliza para crear a xeometria das colisions do corpo rixido
	body->setUserPointer(user);
	body->setCollisionFlags(body->getCollisionFlags() | rbType);
}

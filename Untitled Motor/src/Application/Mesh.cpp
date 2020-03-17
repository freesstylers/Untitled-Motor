#include "Mesh.h"
#include "Transform.h"
#include "Core.h"

Mesh::Mesh(json& args) : Component(args)
{
	Ogre::String mesh = args["mesh"];
	ogreEnt = Core::getInstance()->getSM()->createEntity(mesh);

	if(!args["material"].is_null())
		ogreEnt->setMaterialName(args["material"]);

	isAnimated = ((!args["isAnimated"].is_null()) && (args["isAnimated"]));
}

void Mesh::init(json& args)
{
	e_->getComponent<Transform>("Transform")->getNode()->attachObject(ogreEnt);
}

Mesh::~Mesh()
{
	Component::~Component();
	delete ogreEnt;
}

Ogre::AxisAlignedBox Mesh::getAABB()	const
{
	return ogreEnt->getBoundingBox();
}

Ogre::Real Mesh::getAABBRadius()	const
{
	return ogreEnt->getBoundingRadius();
}

Ogre::Entity* Mesh::getEntity()	const
{
	return ogreEnt;
}

Ogre::Mesh* Mesh::getMesh()	const
{
	return ogreEnt->getMesh().getPointer();
}

bool Mesh::isMeshAnimated() const
{
	return isAnimated;
}

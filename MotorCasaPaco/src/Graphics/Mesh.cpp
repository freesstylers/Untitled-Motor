#include "Graphics/Mesh.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include <Ogre.h>
#include "checkML.h"

Mesh::Mesh(json& args) : Component(args)
{
}

void Mesh::init(json& args)
{
	std::string cast = args["mesh"];
	meshFile = cast;
	ogreEnt = MotorCasaPaco::getInstance()->getSM()->createEntity(meshFile);
	castShadow = true;

	if (!args["material"].is_null())
	{
		std::string aux = args["material"];
		materialName = aux;
		ogreEnt->setMaterialName(args["material"]);
	}

	if (!args["castShadow"].is_null())
		castShadow = args["castShadow"];

	isAnimated = ((!args["isAnimated"].is_null()) && (args["isAnimated"]));

	ogreEnt->setCastShadows(castShadow);

	e_->getComponent<Transform>("Transform")->getNode()->attachObject(ogreEnt);
}

void Mesh::redefine(json& args)
{
	e_->getComponent<Transform>("Transform")->getNode()->detachObject(ogreEnt);
	delete ogreEnt;
	ogreEnt = nullptr;

	if (args["mesh"].is_null())
		args["mesh"] = meshFile;

	if (args["material"].is_null())
		args["material"] = materialName;

	if (args["isAnimated"].is_null())
		args["isAnimated"] = isAnimated;

	init(args);
}

Mesh::~Mesh()
{
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

Ogre::Entity* Mesh::getOgreEntity()	const
{
	return ogreEnt;
}

Ogre::Mesh* Mesh::getMesh()	const
{
	return ogreEnt->getMesh().get();
}

bool Mesh::isMeshAnimated() const
{
	return isAnimated;
}
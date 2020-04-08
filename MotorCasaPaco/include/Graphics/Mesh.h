#pragma once
#include "Entity/Component.h"
#include <OgreEntity.h>
#include <OgreAxisAlignedBox.h>

class Mesh :
	public Component
{
public:
	Mesh(json& args);
	void init(json& args) override;
	void redefine(json& args) override;
	~Mesh() override;

	Ogre::AxisAlignedBox getAABB()	const;
	Ogre::Real getAABBRadius()	const;
	Ogre::Entity* getOgreEntity()	const;
	Ogre::Mesh* getMesh()	const;

	bool isMeshAnimated() const;

private:
	Ogre::Entity* ogreEnt;
	bool isAnimated;

	Ogre::String meshFile;
	Ogre::String materialName;

	bool castShadow;
};

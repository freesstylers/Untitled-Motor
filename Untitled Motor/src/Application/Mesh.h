#pragma once
#include "Component.h"
#include <OgreEntity.h>
#include <OgreAxisAlignedBox.h>

class Mesh :
	public Component
{
public:
	Mesh(json& args);
	void init(json& args) override;
	~Mesh() override;

	Ogre::AxisAlignedBox getAABB()	const;
	Ogre::Real getAABBRadius()	const;
	Ogre::Entity* getOgreEntity()	const;
	Ogre::Mesh* getMesh()	const;

	bool isMeshAnimated() const;

private:
	Ogre::Entity* ogreEnt;
	bool isAnimated;
};


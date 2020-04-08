#pragma once
#include "Entity/Component.h"
#include "Ogre.h"

class TerrainRotation : public Component
{
public:
	TerrainRotation(json& args);
	virtual void start();
	virtual void update();
	~TerrainRotation();
private:
	float speed = 20;
	Ogre::Vector3 rotation;
};
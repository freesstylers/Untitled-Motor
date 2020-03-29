#pragma once
#include "Component.h"
#include "Ogre.h"

class TerrainRotation : public Component
{
public:
	TerrainRotation(json& args);
	virtual void start();
	virtual void update();
	~TerrainRotation();
private:
	float speed = 60;
	float deadZoneX;
	float deadZoneY;
	float deadZoneRange;
	Ogre::Vector3 rotation;
};


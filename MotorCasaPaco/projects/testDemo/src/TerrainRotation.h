#pragma once
#include "Entity/Component.h"

class TerrainRotation : public Component
{
public:
	TerrainRotation(json& args);
	virtual void start();
	virtual void update();
	~TerrainRotation();
private:
	float speed = 20;
	Vector3 rotation;
};
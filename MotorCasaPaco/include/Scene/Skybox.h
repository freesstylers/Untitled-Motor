#pragma once

#include <string>

#include "Entity/Component.h"

namespace Ogre {
	class Plane;
}

class Skybox :
	public Component
{
public:
	enum SkyType {BOX, DOME, PLANE};

	Skybox(json& args);
	~Skybox() override;
	void init(json& args) override;
	void redefine(json& args) override;

	void setEnabled(bool b);

private:
	void makeSky();

	SkyType skyType;
	std::string material;
	float distance;
	bool drawFirst;

	float curvature;
	float tiling;

	Ogre::Plane plane;
	Vector3 normal;
	float scale;
	float bow;
	int xSegments;
	int ySegments;
};


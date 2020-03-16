#pragma once
#include "Component.h"
#include "Ogre.h"

class TransformComponent : public Component
{
public:
	TransformComponent(std::string tag);
	Ogre::Vector3 getPosition();
	Ogre::Quaternion getRotation();
	Ogre::Vector3 getScale();
	void setPosition(Ogre::Vector3 pos);
	void setRotation(Ogre::Quaternion rot);
	void setScale(Ogre::Vector3 s);
private:
	Ogre::Vector3 position;
	Ogre::Quaternion rotation;
	Ogre::Vector3 scale;
};
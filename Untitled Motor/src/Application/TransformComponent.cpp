#include "TransformComponent.h"

TransformComponent::TransformComponent(std::string tag):Component(tag)
{
	position = Ogre::Vector3();
	rotation = Ogre::Quaternion();
	scale = Ogre::Vector3(1, 1, 1);
}

Ogre::Vector3 TransformComponent::getPosition()
{
	return position;
}

Ogre::Quaternion TransformComponent::getRotation()
{
	return rotation;
}

Ogre::Vector3 TransformComponent::getScale()
{
	return scale;
}

void TransformComponent::setPosition(Ogre::Vector3 pos)
{
	position = pos;
}

void TransformComponent::setRotation(Ogre::Quaternion rot)
{
	rotation = rot;
}

void TransformComponent::setScale(Ogre::Vector3 s)
{
	scale = s;
}

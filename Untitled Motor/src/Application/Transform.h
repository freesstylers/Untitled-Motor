#pragma once
#include <Ogre.h>
#include "Component.h"

class Transform :
	public Component
{
public:
	Transform(json& args);
	~Transform() override;
	Ogre::Vector3 getPosition() const;
	Ogre::Quaternion getRotation() const;
	Ogre::Vector3 getScale() const;

	Ogre::Vector3 getWorldPosition() const;
	Ogre::Quaternion getWorldRotation() const;
	Ogre::Vector3 getWorldScale() const;

	void setPosition(Ogre::Vector3 pos);
	void setRotation(Ogre::Quaternion rot);
	void setRotation(Ogre::Vector3 rot);
	void setScale(Ogre::Vector3 s);

	void setWorldPosition(Ogre::Vector3 pos);
	void setWorldRotation(Ogre::Quaternion rot);
	void setWorldRotation(Ogre::Vector3 rot);
	void setWorldScale(Ogre::Vector3 s);

	void translate(Ogre::Vector3 pos, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	void rotate(Ogre::Quaternion rot, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	void rotate(Ogre::Vector3 rot, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL);
	void scale(Ogre::Vector3 s);

	Ogre::SceneNode* getNode();

private:
	bool ReceiveEvent(Event& event) override;

	Ogre::SceneNode* node;
};


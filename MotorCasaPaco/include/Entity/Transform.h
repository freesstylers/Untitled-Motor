#pragma once
#include "Entity/Component.h"

namespace Ogre {
	class MovableObject;
	class Node;
	class SceneNode;
}

class Transform :
	public Component
{
public:
	Transform(json& args);
	~Transform() override;
	void init(json& args) override;
	void redefine(json& args) override;
	Vector3 getPosition() const;
	Quaternion getRotation() const;
	Vector3 getScale() const;

	Vector3 getWorldPosition() const;
	Quaternion getWorldRotation() const;
	Vector3 getWorldScale() const;

	void setPosition(Vector3 pos);
	void setRotation(Quaternion rot);
	void setRotation(Vector3 rot);
	void setScale(Vector3 s);

	void setWorldPosition(Vector3 pos);
	void setWorldRotation(Quaternion rot);
	void setWorldRotation(Vector3 rot);
	void setWorldScale(Vector3 s);
	void setInheritedRotation(bool set);

	void translate(Vector3 pos, TransformSpace relativeTo = TransformSpace::LOCAL);
	void rotate(Quaternion rot, TransformSpace relativeTo = TransformSpace::LOCAL);
	void rotate(Vector3 rot, TransformSpace relativeTo = TransformSpace::LOCAL);
	void scale(Vector3 s);

	void attachNode(Ogre::Node* node);
	void attachNode(Ogre::SceneNode* node);
	void attachObject(Ogre::MovableObject* obj);
	void detachObject(std::string& name);
	void detachNode(std::string& name);

	void rotateAroundPivot(Vector3 rot, Ogre::SceneNode* pivot);
	void rotateAroundPivot(Quaternion rot, Ogre::SceneNode* pivot);
	void rotateAroundPivot(Vector3 rot, Entity* pivot);
	void rotateAroundPivot(Quaternion rot, Entity* pivot);

	void lookAt(Vector3 dir, Vector3 localDir = Vector3(0, 1, 0), TransformSpace relativeTo = TransformSpace::WORLD);

	Ogre::SceneNode* getNode();

	void onSetParent(Entity* parent) override;

private:
	Ogre::SceneNode* node = nullptr;
};


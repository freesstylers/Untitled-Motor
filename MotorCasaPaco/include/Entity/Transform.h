#pragma once
#include "Entity/Component.h"

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

	Ogre::SceneNode* getNode();

	void onSetParent(Entity* parent) override;

private:
	Ogre::SceneNode* node = nullptr;
};


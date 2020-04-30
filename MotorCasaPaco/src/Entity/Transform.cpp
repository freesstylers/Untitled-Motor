
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "checkML.h"

#include <Ogre.h>

Transform::Transform(json& args) : Component(args)
{

}

void Transform::init(json& args)
{
	node = MotorCasaPaco::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode(args["name"]);
	node->setInheritScale(false);

	Vector3 position = Vector3(0, 0, 0);
	Vector3 rotation = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);
	if (!args["position"].is_null()) {
		position.X = args["position"][0];
		position.Y = args["position"][1];
		position.Z = args["position"][2];
	}
	if (!args["rotation"].is_null()) {
		rotation.X = args["rotation"][0];
		rotation.Y = args["rotation"][1];
		rotation.Z = args["rotation"][2];
	}
	if (!args["scale"].is_null()) {
		scale.X = args["scale"][0];
		scale.Y = args["scale"][1];
		scale.Z = args["scale"][2];
	}

	setPosition(position);
	setRotation(rotation);
	setScale(scale);
}

void Transform::redefine(json& args)
{
	Quaternion origRotation = getRotation();

	if (args["name"].is_null())
		args["name"] = node->getName();

	if (args["position"].is_null())
		args["position"] = { getPosition().X, getPosition().Y, getPosition().Z };

	if (args["scale"].is_null())
		args["scale"] = { getScale().X, getScale().Y, getScale().Z };

	std::vector<Ogre::MovableObject*> obj = node->getAttachedObjects();
	std::vector<Ogre::Node*> children = node->getChildren();
	node->getParent()->removeChild(node->getName());
	MotorCasaPaco::getInstance()->getSM()->destroySceneNode(node->getName());
	node = nullptr;

	init(args);

	for (Ogre::MovableObject* n : obj)
		node->attachObject(n);
	
	for (Ogre::Node* n : children)
		node->addChild(n);

	//separate because the constructor for transform takes euler angles, and translating from quaternion to euler can lead to errors, so the rotation is "reset" after init()
	if (args["rotation"].is_null())
		setRotation(origRotation);
}

Transform::~Transform()
{
	Component::~Component();

	if (node == nullptr)
		return;

	node->detachAllObjects();
	MotorCasaPaco::getInstance()->getSM()->destroySceneNode(node->getName());
	node = nullptr;

}

Vector3 Transform::getPosition() const
{
	return (Vector3)node->getPosition();
}
Quaternion Transform::getRotation() const
{
	return (Quaternion)node->getOrientation();
}
Vector3 Transform::getScale() const
{
	return (Vector3)node->getScale();
}

Vector3 Transform::getWorldPosition() const
{
	return (Vector3)node->getParent()->convertLocalToWorldPosition(node->getPosition());
}
Quaternion Transform::getWorldRotation() const
{
	return (Quaternion)node->getParent()->convertLocalToWorldOrientation(node->getOrientation());
}
Vector3 Transform::getWorldScale() const
{
	//this might not work properly, should test it
	return (Vector3)node->_getDerivedScale();
}


void Transform::setPosition(Vector3 pos)
{
	node->setPosition(pos);
}
void Transform::setRotation(Quaternion rot)
{
	node->setOrientation(rot);
}
void Transform::setRotation(Vector3 rot)
{
	setRotation(Quaternion::FromEuler(rot));
}
void Transform::setScale(Vector3 s)
{
	node->setScale(s);
}


void Transform::setWorldPosition(Vector3 pos)
{
	node->setPosition(node->getParent()->convertWorldToLocalPosition(pos));
}
void Transform::setWorldRotation(Quaternion rot)
{
	node->setOrientation(node->getParent()->convertWorldToLocalOrientation(rot));
}
void Transform::setWorldRotation(Vector3 rot)
{
	//complete when hierarchy is implemented
	setRotation(Quaternion::FromEuler(rot));
}
void Transform::setWorldScale(Vector3 s)
{
	//complete when hierarchy is implemented
	node->setScale(s);
}
void Transform::setInheritedRotation(bool set)
{
	node->setInheritOrientation(set);
}


void Transform::attachObject(Ogre::MovableObject* obj)
{
	node->attachObject(obj);
}

void Transform::attachNode(Ogre::Node* n)
{
	node->addChild(n);
}

void Transform::attachNode(Ogre::SceneNode* n)
{
	node->addChild(n);
}

void Transform::detachObject(std::string& name)
{
	node->detachObject(name);
}

void Transform::detachNode(std::string& name)
{
	node->removeChild(name);
}


void Transform::translate(Vector3 pos, TransformSpace relativeTo)
{
	node->translate(pos, (Ogre::Node::TransformSpace)relativeTo);
}
void Transform::rotate(Quaternion rot, TransformSpace relativeTo)
{
	node->rotate(rot, (Ogre::Node::TransformSpace)relativeTo);
}
void Transform::rotate(Vector3 rot, TransformSpace relativeTo)
{
	Quaternion quat = Quaternion::FromEuler(rot);
	rotate(Quaternion::FromEuler(rot), relativeTo);
}
void Transform::scale(Vector3 s)
{
	node->scale(s);
}

Ogre::SceneNode* Transform::getNode()
{
	return node;
}

void Transform::onSetParent(Entity* parent)
{
	Ogre::Node* nParent = parent->getComponent<Transform>("Transform")->getNode();
	Ogre::Node* currentParent = node->getParent();

	Vector3 nodeWorldPos = (Vector3)currentParent->convertLocalToWorldPosition(node->getPosition());
	Vector3 resultPosition = (Vector3)nParent->convertWorldToLocalPosition(nodeWorldPos);
	Quaternion nodeWorldOrientation = (Quaternion)currentParent->convertLocalToWorldOrientation(node->getOrientation());
	Quaternion resultOrientation = (Quaternion)nParent->convertWorldToLocalOrientation(nodeWorldOrientation);

	currentParent->removeChild(node);
	nParent->addChild(node);
	node->setPosition(resultPosition);
	node->setOrientation(resultOrientation);
	nParent->needUpdate(true);
}
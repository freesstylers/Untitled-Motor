#include "Transform.h"
#include "Core.h"

Transform::Transform(json& args) : Component(args)
{
	node = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode(args["name"]);

	Ogre::Vector3 position = Ogre::Vector3(0, 0, 0);
	Ogre::Vector3 rotation = Ogre::Vector3(0, 0, 0);
	Ogre::Vector3 scale = Ogre::Vector3(1, 1, 1);
	if (!args["position"].is_null()) {
		position.x = args["position"][0];
		position.y = args["position"][1];
		position.z = args["position"][2];
	}
	if (!args["rotation"].is_null()) {
		rotation.x = args["rotation"][0];
		rotation.y = args["rotation"][1];
		rotation.z = args["rotation"][2];
	}
	if (!args["scale"].is_null()) {
		scale.x = args["scale"][0];
		scale.y = args["scale"][1];
		scale.z = args["scale"][2];
	}

	setPosition(position);
	setRotation(rotation);
	setScale(scale);

	std::cout << args["type"] << ": " << args["tag"] << " " << position << " " << scale << " " << rotation << "\n";
}

Transform::~Transform()
{
	node->removeAndDestroyAllChildren();
	node->getParent()->removeChild(node->getName());
	delete node;
}

bool Transform::ReceiveEvent(Event& event)
{
	return false;
}

Ogre::Vector3 Transform::getPosition() const
{
	return node->getPosition();
}
Ogre::Quaternion Transform::getRotation() const
{
	return node->getOrientation();
}
Ogre::Vector3 Transform::getScale() const
{
	return node->getScale();
}

Ogre::Vector3 Transform::getWorldPosition() const
{
	return Core::getInstance()->getSM()->getRootSceneNode()->convertLocalToWorldPosition(node->getPosition());
}
Ogre::Quaternion Transform::getWorldRotation() const
{
	return Core::getInstance()->getSM()->getRootSceneNode()->convertLocalToWorldOrientation(node->getOrientation());
}
Ogre::Vector3 Transform::getWorldScale() const
{
	//this might not work properly, should test it
	return node->_getDerivedScale();
}


void Transform::setPosition(Ogre::Vector3 pos)
{
	node->setPosition(pos);
}
void Transform::setRotation(Ogre::Quaternion rot)
{
	node->setOrientation(rot);
}
void Transform::setRotation(Ogre::Vector3 rot)
{
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesZYX(Ogre::Radian(Ogre::Degree(rot.z)), Ogre::Radian(Ogre::Degree(rot.y)), Ogre::Radian(Ogre::Degree(rot.x)));
	setRotation(Ogre::Quaternion(mx));
}
void Transform::setScale(Ogre::Vector3 s)
{
	node->setScale(s);
}


void Transform::setWorldPosition(Ogre::Vector3 pos)
{
	//complete when hierarchy is implemented
	node->setPosition(pos);
}
void Transform::setWorldRotation(Ogre::Quaternion rot)
{
	//complete when hierarchy is implemented
	node->setOrientation(rot);
}
void Transform::setWorldRotation(Ogre::Vector3 rot)
{
	//complete when hierarchy is implemented
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesZYX(Ogre::Radian(Ogre::Degree(rot.z)), Ogre::Radian(Ogre::Degree(rot.y)), Ogre::Radian(Ogre::Degree(rot.x)));
	setRotation(Ogre::Quaternion(mx));
}
void Transform::setWorldScale(Ogre::Vector3 s)
{
	//complete when hierarchy is implemented
	node->setScale(s);
}


void Transform::translate(Ogre::Vector3 pos, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL)
{
	node->translate(pos, relativeTo);
}
void Transform::rotate(Ogre::Quaternion rot, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL)
{
	node->rotate(rot, relativeTo);
}
void Transform::rotate(Ogre::Vector3 rot, Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_LOCAL)
{
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesZYX(Ogre::Radian(Ogre::Degree(rot.z)), Ogre::Radian(Ogre::Degree(rot.y)), Ogre::Radian(Ogre::Degree(rot.x)));
	rotate(Ogre::Quaternion(mx), relativeTo);
}
void Transform::scale(Ogre::Vector3 s)
{
	node->scale(s);
}



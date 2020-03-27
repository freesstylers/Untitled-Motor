#include "Transform.h"
#include "Core.h"

Transform::Transform(json& args) : Component(args)
{
	node = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode(args["name"]);
	node->setInheritScale(false);

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
}

Transform::~Transform()
{
	Component::~Component();
	node->removeAndDestroyAllChildren();
	node->getParent()->removeChild(node->getName());
	delete node;
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
	return node->getParent()->convertLocalToWorldPosition(node->getPosition());
}
Ogre::Quaternion Transform::getWorldRotation() const
{
	return node->getParent()->convertLocalToWorldOrientation(node->getOrientation());
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
	node->setPosition(node->getParent()->convertWorldToLocalPosition(pos));
}
void Transform::setWorldRotation(Ogre::Quaternion rot)
{
	node->setOrientation(node->getParent()->convertLocalToWorldOrientation(rot));
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


void Transform::translate(Ogre::Vector3 pos, Ogre::Node::TransformSpace relativeTo)
{
	node->translate(pos, relativeTo);
}
void Transform::rotate(Ogre::Quaternion rot, Ogre::Node::TransformSpace relativeTo)
{
	node->rotate(rot, relativeTo);
}
void Transform::rotate(Ogre::Vector3 rot, Ogre::Node::TransformSpace relativeTo)
{
	Ogre::Matrix3 mx;
	mx.FromEulerAnglesZYX(Ogre::Radian(Ogre::Degree(rot.z)), Ogre::Radian(Ogre::Degree(rot.y)), Ogre::Radian(Ogre::Degree(rot.x)));
	rotate(Ogre::Quaternion(mx), relativeTo);
}
void Transform::scale(Ogre::Vector3 s)
{
	node->scale(s);
}

Ogre::SceneNode* Transform::getNode()
{
	return node;
}

bool Transform::ReceiveEvent(Event& event)
{
	if (event.type == EventType::SETPARENT) {
		SetParentEvent parentEvent = static_cast<SetParentEvent&>(event);
		Ogre::Node* nParent = parentEvent.parent->getComponent<Transform>("Transform")->getNode();
		Ogre::Node* currentParent = node->getParent();

		Ogre::Vector3 nodeWorldPos = currentParent->convertLocalToWorldPosition(node->getPosition());
		Ogre::Vector3 resultPosition = nParent->convertWorldToLocalPosition(nodeWorldPos);
		Ogre::Quaternion nodeWorldOrientation = currentParent->convertLocalToWorldOrientation(node->getOrientation());
		Ogre::Quaternion resultOrientation = nParent->convertWorldToLocalOrientation(nodeWorldOrientation);

		currentParent->removeChild(node);
		nParent->addChild(node);
		node->setPosition(resultPosition);
		node->setOrientation(resultOrientation);
		nParent->needUpdate(true);
		node->needUpdate(true);
	}

	return false;
}

#include "Transform.h"
#include "Core.h"

Transform::Transform(json& args) : Component(args)
{
	node = Core::getInstance()->getSM()->getRootSceneNode()->createChildSceneNode(args["name"]);

	position = Ogre::Vector3(0, 0, 0);
	rotation = Ogre::Vector3(0, 0, 0);
	scale = Ogre::Vector3(1, 1, 1);
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

	node->translate(position);
	node->scale(scale);
	node->pitch(Ogre::Degree(rotation.x));
	node->yaw(Ogre::Degree(rotation.y));
	node->roll(Ogre::Degree(rotation.z));

	std::cout << args["type"] << ": " << args["tag"] << " " << position << " " << scale << " " << rotation << "\n";
}

bool Transform::ReceiveEvent(Event& event)
{
	return false;
}

#include "SimpleMovement.h"
#include "InputManager.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"
#include "Core.h"
#include "Ogre.h"

SimpleMovement::SimpleMovement(json& args) : Component(args)
{
	speed = args["speed"];
	rotateSpeed = args["rotateSpeed"];
}

SimpleMovement::~SimpleMovement()
{

}

void SimpleMovement::start()
{

}

void SimpleMovement::update()
{
	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->rotate(Ogre::Vector3(0, rotateSpeed * Core::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->rotate(Ogre::Vector3(0, - rotateSpeed * Core::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->translate(Ogre::Vector3(0, 0, - speed * Core::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->translate(Ogre::Vector3(0, 0, speed * Core::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}
}

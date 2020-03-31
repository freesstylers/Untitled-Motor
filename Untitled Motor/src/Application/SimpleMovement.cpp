#include "SimpleMovement.h"
#include "InputManager.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
SimpleMovement::SimpleMovement(json& args) : Component(args)
{
	speed = args["speed"];
	rotateSpeed = args["rotateSpeed"];
}

void SimpleMovement::start()
{

}

void SimpleMovement::update()
{
	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->setRotation(transform->getRotation + (rotateSpeed * Core::getInstance()->DeltaTime() / 1000.0f));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->setRotation(transform->getRotation - (rotateSpeed * Core::getInstance()->DeltaTime() / 1000.0f));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		Transform* transform = getEntity()->getComponent<Transform>("Transform");
		transform->setPosition(transform->getPosition - (spee))
	}
}

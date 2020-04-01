#include "SimpleMovement.h"
#include "InputManager.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Entity.h"
#include "Core.h"
#include "Ogre.h"

SimpleMovement::SimpleMovement(json& args) : Component(args)
{
	if(!args["speed"].is_null())
		speed = args["speed"];
	if(!args["rotateSpeed"].is_null())
		rotateSpeed = args["rotateSpeed"];
	if (!args["controller"].is_null())
		onlycontroller = args["onlycontroller"];

	deadZoneX = deadZoneX / 32768.0;
	deadZoneY = deadZoneY / 32768.0;
	deadZoneRange = 0.10;
}


void SimpleMovement::start()
{

}

void SimpleMovement::update()
{
	if(!onlycontroller)
		keyboardMovement();
	controllerMovement();
}

void SimpleMovement::controllerMovement()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");

	float leftx = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	float lefty = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);

	float rightx = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTX);
	float righty = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTY);

	leftx = leftx / 32768.0;
	lefty = lefty / 32768.0;
	rightx = rightx / 32768.0;
	righty = righty / 32768.0;

	if (leftx <= deadZoneX + deadZoneRange && leftx >= deadZoneX - deadZoneRange) {
		leftx = 0;
	}

	if (lefty <= deadZoneX + deadZoneRange && lefty >= deadZoneX - deadZoneRange) {
		lefty = 0;
	}

	if (righty <= deadZoneY + deadZoneRange && righty >= deadZoneY - deadZoneRange) {
		righty = 0;
	}

	if (rightx <= deadZoneY + deadZoneRange && rightx >= deadZoneY - deadZoneRange) {
		rightx = 0;
	}

	transform->translate(Ogre::Vector3(speed * leftx * Core::getInstance()->DeltaTime(), 0, speed * lefty * Core::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	transform->rotate(Ogre::Vector3(rotateSpeed * -righty * Core::getInstance()->DeltaTime(), rotateSpeed * -rightx * Core::getInstance()->DeltaTime(), 0));
}

void SimpleMovement::keyboardMovement()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		transform->rotate(Ogre::Vector3(0, -rotateSpeed * Core::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		transform->rotate(Ogre::Vector3(0, rotateSpeed * Core::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		transform->translate(Ogre::Vector3(0, 0, speed * Core::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		transform->translate(Ogre::Vector3(0, 0, -speed * Core::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}
}

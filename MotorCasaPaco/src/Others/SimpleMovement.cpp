#include "Others/SimpleMovement.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"
#include "Physics/RigidBody.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include "Ogre.h"

SimpleMovement::SimpleMovement(json& args) : Component(args)
{

}

void SimpleMovement::init(json& args)
{
	speed = 1.0;
	rotateSpeed = 1.0;
	onlycontroller = false;
	if (!args["speed"].is_null())
		speed = args["speed"];
	if (!args["rotateSpeed"].is_null())
		rotateSpeed = args["rotateSpeed"];
	if (!args["controller"].is_null())
		onlycontroller = args["onlycontroller"];

}

void SimpleMovement::redefine(json& args)
{
	if (args["speed"].is_null())
		args["speed"] = speed;
	if (args["rotateSpeed"].is_null())
		args["rotateSpeed"] = rotateSpeed;
	if (args["controller"].is_null())
		args["onlycontroller"] = onlycontroller;

	init(args);
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

	float leftx = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX, false);
	float lefty = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY, false);

	float rightx = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTX, false);
	float righty = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTY, false);


	transform->translate(Ogre::Vector3(speed * leftx * MotorCasaPaco::getInstance()->DeltaTime(), 0, speed * lefty * MotorCasaPaco::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	transform->rotate(Ogre::Vector3(rotateSpeed * -righty * MotorCasaPaco::getInstance()->DeltaTime(), rotateSpeed * -rightx * MotorCasaPaco::getInstance()->DeltaTime(), 0));
}

void SimpleMovement::keyboardMovement()
{
	Transform* transform = getEntity()->getComponent<Transform>("Transform");
	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		transform->rotate(Ogre::Vector3(0, -rotateSpeed * MotorCasaPaco::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		transform->rotate(Ogre::Vector3(0, rotateSpeed * MotorCasaPaco::getInstance()->DeltaTime(), 0));
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		transform->translate(Ogre::Vector3(0, 0, speed * MotorCasaPaco::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}

	if (InputManager::getInstance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		transform->translate(Ogre::Vector3(0, 0, -speed * MotorCasaPaco::getInstance()->DeltaTime()), Ogre::Node::TS_LOCAL);
	}
}

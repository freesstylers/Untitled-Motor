#include "MarbleMovementTest.h"
#include "Entity.h"
#include "RigidBody.h"
#include "InputManager.h"
#include "Core.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>

MarbleMovementTest::MarbleMovementTest(json& args):Component(args) {

}

bool MarbleMovementTest::ReceiveEvent(Event& event)
{
	return false;
}

void MarbleMovementTest::update()
{
	float deltatime = 1/60.0;
	if (InputManager::getInstance()->GameControllerIsButtonDown(SDL_CONTROLLER_BUTTON_X)) {
		getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(-1, 0, 0) * speed * deltatime);
	}
	if (InputManager::getInstance()->GameControllerIsButtonDown(SDL_CONTROLLER_BUTTON_B)) {
		getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(1, 0, 0) * speed * deltatime);
	}
	if (InputManager::getInstance()->GameControllerIsButtonDown(SDL_CONTROLLER_BUTTON_Y)) {
		getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(0, 0, -1) * speed * deltatime);
	}
	if (InputManager::getInstance()->GameControllerIsButtonDown(SDL_CONTROLLER_BUTTON_A)) {
		getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(0, 0, 1) * speed * deltatime);
	}
}

MarbleMovementTest::~MarbleMovementTest()
{

}

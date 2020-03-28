#include "MarbleMovementTest.h"
#include "Entity.h"
#include "RigidBody.h"
#include "InputManager.h"
#include "Core.h"
#include "btBulletDynamicsCommon.h"
#include <iostream>

MarbleMovementTest::MarbleMovementTest(json& args):Component(args) {
	deadZoneX = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	deadZoneY = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	deadZoneX = deadZoneX / 32768.0;
	deadZoneY = deadZoneY / 32768.0;
	deadZoneRange = 0.15;
}

bool MarbleMovementTest::ReceiveEvent(Event& event)
{
	return false;
}

void MarbleMovementTest::start()
{
	getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->setActivationState(DISABLE_DEACTIVATION);
}

void MarbleMovementTest::update()
{
	/*float deltatime = 1/60.0;
	float x = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	float y = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	x = x / 32768.0;
	y = y / 32768.0;

	if (x <= deadZoneX + deadZoneRange && x >= deadZoneX - deadZoneRange) {
		x = 0;
		std::cout << "Zona muerta X" << "\n";
	}
	else 		std::cout << "Zona viva X" << "\n";

	if (y <= deadZoneY + deadZoneRange && y >= deadZoneY - deadZoneRange) {
		y = 0;
		std::cout << "Zona muerta Y" << "\n";
	}
	else 		std::cout << "Zona viva Y" << "\n";

	getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->activate(true);
	getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(x, 0, y) * speed * deltatime);*/
}

MarbleMovementTest::~MarbleMovementTest()
{

}

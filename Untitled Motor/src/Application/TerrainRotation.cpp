#include "TerrainRotation.h"
#include "InputManager.h"
#include <iostream>
#include "Transform.h"
#include "Entity.h"
#include "RigidBody.h"
#include "btBulletDynamicsCommon.h"

TerrainRotation::TerrainRotation(json& args):Component(args)
{
	deadZoneX = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	deadZoneY = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	deadZoneX = deadZoneX / 32768.0;
	deadZoneY = deadZoneY / 32768.0;
	deadZoneRange = 0.10;
}

void TerrainRotation::update()
{
	float deltatime = 1 / 60.0;
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

	x *= 10;
	y *= 10;

	int xdir = 1;
	int ydir = 1;

	if (x < 0) xdir = -1;
	if (y < 0) ydir = -1;

	x = x * x;
	y = y * y;


	Transform* transform = getEntity()->getComponent<Transform>("Transform");

	x = x / (10 * 10);
	y = y / (10 * 10);

	x = x * 90 * xdir;
	y = y * 90 * ydir;
	transform->setRotation(Ogre::Vector3(y, 0, -x));
}

TerrainRotation::~TerrainRotation()
{

}
#include "Others/ForcesTest.h"
#include "Input/InputManager.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"

ForcesTest::ForcesTest(json& args):Component(args)
{

}

void ForcesTest::start()
{
	deadZoneX = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	deadZoneY = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	deadZoneX = deadZoneX / 32768.0;
	deadZoneY = deadZoneY / 32768.0;
	deadZoneRange = 0.10;
}

void ForcesTest::update()
{
	float x = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	float y = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	x = x / 32768.0;
	y = y / 32768.0;

	if (x <= deadZoneX + deadZoneRange && x >= deadZoneX - deadZoneRange) {
		x = 0;
		//std::cout << "Zona muerta X" << "\n";
	}
	/*else 		std::cout << "Zona viva X" << "\n";*/

	if (y <= deadZoneY + deadZoneRange && y >= deadZoneY - deadZoneRange) {
		y = 0;
		//std::cout << "Zona muerta Y" << "\n";
	}
	//else		std::cout << "Zona viva Y" << "\n";

	x *= 10;
	y *= 10;

	int xdir = 1;
	int ydir = 1;

	if (x < 0) xdir = -1;
	if (y < 0) ydir = -1;

	x = x * x;
	y = y * y;

	x = x / (10 * 10);
	y = y / (10 * 10);

	getEntity()->getComponent<RigidBody>("RigidBody")->applyForce(LINEAR_VELOCITY, btVector3(xdir* x, 0, ydir*y) * speed);
}

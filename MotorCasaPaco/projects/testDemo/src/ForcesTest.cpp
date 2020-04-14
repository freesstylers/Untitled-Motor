#include "ForcesTest.h"
#include "Input/InputManager.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"

ForcesTest::ForcesTest(json& args):Component(args)
{

}

void ForcesTest::start()
{
}

void ForcesTest::update()
{
	float x = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	float y = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);
	
	getEntity()->getComponent<RigidBody>("RigidBody")->applyForce(LINEAR_VELOCITY, Vector3( x, 0, y) * speed);
}

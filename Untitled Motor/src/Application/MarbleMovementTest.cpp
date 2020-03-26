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
	int x = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX);
	int y = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY);
	float x_=x / 32768.0;
	float y_=y / 32768.0;
	if (x_ < 0.1 && x_ > -0.1) x_ = 0;
	if (y<0.1 && y_ > -0.1) y_ = 0;
	getEntity()->getComponent<RigidBody>("RigidBody")->getRigidBody()->applyCentralImpulse(btVector3(x_, 0, y_) * speed * deltatime);
}

MarbleMovementTest::~MarbleMovementTest()
{

}

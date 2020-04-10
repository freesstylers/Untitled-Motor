#include "Others/TerrainRotation.h"
#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"
#include "Audio/AudioManager.h"
#include "MotorCasaPaco.h"
#include "btBulletDynamicsCommon.h"

TerrainRotation::TerrainRotation(json& args) :Component(args)
{

}

void TerrainRotation::start()
{
	AudioManager::getInstance()->playMusic("./assets/sound/alma_partia.mp3", 1);
	AudioManager::getInstance()->setVolume(0.1, 1);
	rotation = Ogre::Vector3(0, 0, 0);
}

void TerrainRotation::update()
{
	float deltatime = MotorCasaPaco::getInstance()->DeltaTime();
	deltatime /= 1000.f;
	float x = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX, true);
	float y = InputManager::getInstance()->GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY, true);

	Transform* transform = getEntity()->getComponent<Transform>("Transform");

	x = x * 90;
	y = y * 90;

	Ogre::Vector3 target(y, 0, -x);

	Ogre::Vector3 dir = target - rotation;

	if (dir.length() <= 1) dir = Ogre::Vector3(0, 0, 0);

	float speedmult = dir.length();

	dir.normalise();

	rotation += dir * speed * deltatime * speedmult * 0.5;
	transform->setRotation((Vector3)rotation);

	if (InputManager::getInstance()->GameControllerIsButtonDown(SDL_CONTROLLER_BUTTON_A) && !AudioManager::getInstance()->isPlayingChannel(0)) {
		FMOD_VECTOR vec{
			transform->getPosition().X,
			transform->getPosition().Y,
			transform->getPosition().Z
		};
		AudioManager::getInstance()->playSound("./assets/sound/movie_1.mp3", 0);
		AudioManager::getInstance()->setVolume(0.5, 0);
	}
}

TerrainRotation::~TerrainRotation()
{

}
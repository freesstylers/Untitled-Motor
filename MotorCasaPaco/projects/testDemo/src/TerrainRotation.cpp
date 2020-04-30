#include "TerrainRotation.h"
#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Transform.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"
#include "Audio/AudioManager.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"

TerrainRotation::TerrainRotation(json& args) :Component(args)
{

}

void TerrainRotation::start()
{
	marble = SceneManager::getInstance()->getCurrentScene()->getEntity("ball");
}

void TerrainRotation::update()
{

	getEntity()->getTransform()->rotateAroundPivot(Vector3(0, 1, 1), marble);

	getEntity()->getTransform()->lookAt(marble->getTransform()->getWorldPosition());
	//float deltatime = MotorCasaPaco::getInstance()->DeltaTime();
	//deltatime /= 1000.f;
	//float x = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, true);
	//float y = InputManager::getInstance()->GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, true);

	//Transform* transform = getEntity()->getComponent<Transform>("Transform");

	//x = x * 90;
	//y = y * 90;

	//Vector3 target(y, 0, -x);

	//Vector3 dir = target - rotation;

	//if (Vector3::Magnitude(dir) <= 1) dir = Vector3(0, 0, 0);

	//float speedmult = Vector3::Magnitude(dir);

	//dir = Vector3::Normalized(dir);

	//rotation += dir * speed * deltatime * speedmult * 0.5;
	//transform->setRotation(rotation);

	//if (InputManager::getInstance()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A) && !AudioManager::getInstance()->isPlayingChannel(0)) {
	//	transform->getPosition(); // Esto no se usa?
	//	AudioManager::getInstance()->playSound("./assets/sound/movie_1.mp3", 0);
	//	AudioManager::getInstance()->setVolume(0.5, 0);
	//}
}

TerrainRotation::~TerrainRotation()
{

}
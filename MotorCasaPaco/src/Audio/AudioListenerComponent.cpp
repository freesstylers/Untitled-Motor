#include "Audio/AudioListenerComponent.h"
#include "MotorCasaPaco.h"
#include "Entity/Transform.h"
#include "Graphics/Camera.h"
#include <fmod.hpp>
#include <fmod.h>
#include "checkML.h"

AudioListenerComponent::AudioListenerComponent(json& args): Component(args)
{
	
}

AudioListenerComponent::~AudioListenerComponent()
{
}

bool AudioListenerComponent::ReceiveEvent(Event& event)
{
	return false;
}

void AudioListenerComponent::update()
{
	pos.X = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.Y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.Z = e_->getComponent<Transform>("Transform")->getPosition().Z;

	forward.X = 0;
	forward.Y = 0;
	forward.Z = 0;

	up.X = 0;
	up.Y = 0;
	up.Z = 0;

	vel.X = 0;
	vel.Y = 0;
	vel.Z = 0;
	AudioManager::getInstance()->updateListener(pos, vel, forward, up);
}


void AudioListenerComponent::init(json& j)
{
	pos.X = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.Y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.Z = e_->getComponent<Transform>("Transform")->getPosition().Z;

	forward.X = 0;
	forward.Y = 0;
	forward.Z = 0;

	up.X = 0;
	up.Y = 0;
	up.Z = 0;

	vel.X = 0;
	vel.Y = 0;
	vel.Z = 0;

	AudioManager::getInstance()->updateListener(pos, vel, forward, up);

}

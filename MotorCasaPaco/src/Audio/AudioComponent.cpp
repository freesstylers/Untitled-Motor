#include "Audio/AudioComponent.h"
#include "MotorCasaPaco.h"
#include "Entity/Transform.h"

#include <fmod.hpp>
#include <fmod.h>

AudioComponent::AudioComponent(json& args): Component(args)
{
	
}

AudioComponent::~AudioComponent()
{
}

bool AudioComponent::ReceiveEvent(Event& event)
{
	return false;
}

void AudioComponent::update()
{
	pos.X = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.Y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.Z = e_->getComponent<Transform>("Transform")->getPosition().Z;

	vel.X = 0;
	vel.Y = 0;
	vel.Z = 0;
	AudioManager::getInstance()->updateSound(pos, vel, numObj, numObj);
}

void AudioComponent::removeEmisor() {
	AudioManager::getInstance()->removeEmisor(numObj);
	numObj = -1;
}

void AudioComponent::init(json& j)
{
	pos.X = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.Y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.Z = e_->getComponent<Transform>("Transform")->getPosition().Z;	

	vel.X = 0;
	vel.Y = 0;
	vel.Z = 0;
	numObj = AudioManager::getInstance()->addEmisor(pos, vel);

	AudioManager::getInstance()->updateSound(pos, vel, numObj, numObj);


	AudioManager::getInstance()->playSound("assets/sound/rock.wav",numObj);
}

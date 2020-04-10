#include "Audio/AudioComponent.h"
#include "MotorCasaPaco.h"
#include "Entity/Transform.h"

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
	pos.x = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.z = e_->getComponent<Transform>("Transform")->getPosition().Z;



	vel.x = 0;
	vel.y = 0;
	vel.z = 0;
	AudioManager::getInstance()->updateSound(pos, vel, numObj, numObj);
}

void AudioComponent::removeEmisor() {
	AudioManager::getInstance()->removeEmisor(numObj);
	numObj = -1;
}

void AudioComponent::init(json& j)
{
	pos.x = e_->getComponent<Transform>("Transform")->getPosition().X;
	pos.y = e_->getComponent<Transform>("Transform")->getPosition().Y;
	pos.z = e_->getComponent<Transform>("Transform")->getPosition().Z;

	

	vel.x = 0;
	vel.y = 0;
	vel.z = 0;
	numObj = AudioManager::getInstance()->addEmisor(pos, vel);

	AudioManager::getInstance()->updateSound(pos, vel, numObj, numObj);


	AudioManager::getInstance()->playSound("assets/sound/rock.wav",numObj);
}

#include "Audio/AudioListenerComponent.h"
#include "Core.h"
#include "Entity/Transform.h"
#include "Graphics/Camera.h"

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
	pos.x = e_->getComponent<Transform>("Transform")->getPosition().x;
	pos.y = e_->getComponent<Transform>("Transform")->getPosition().y;
	pos.z = e_->getComponent<Transform>("Transform")->getPosition().z;

	forward.x = 0;
	forward.y = 0;
	forward.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 0;

	vel.x = 0;
	vel.y = 0;
	vel.z = 0;
	AudioManager::getInstance()->updateListener(pos, vel, forward, up);
}


void AudioListenerComponent::init(json& j)
{
	pos.x = e_->getComponent<Transform>("Transform")->getPosition().x;
	pos.y = e_->getComponent<Transform>("Transform")->getPosition().y;
	pos.z = e_->getComponent<Transform>("Transform")->getPosition().z;

	forward.x = 0;
	forward.y = 0;
	forward.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 0;

	vel.x = 0;
	vel.y = 0;
	vel.z = 0;

	AudioManager::getInstance()->updateListener(pos, vel, forward, up);

}

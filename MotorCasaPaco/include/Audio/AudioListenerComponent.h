#pragma once

#include "Entity/Component.h"
#include <fmod.hpp>
#include <fmod.h>
#include "Audio/AudioManager.h"

class AudioListenerComponent : public Component
{
public:
	AudioListenerComponent(json& args);
	~AudioListenerComponent();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

private:

	Vector3 forward;
	Vector3 up;

	Vector3 pos;
	Vector3 vel;
};




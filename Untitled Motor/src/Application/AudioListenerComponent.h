#pragma once

#include "Component.h"
#include <fmod.hpp>
#include <fmod.h>
#include "AudioManager.h"

class AudioListenerComponent : public Component
{
public:
	AudioListenerComponent(json& args);
	~AudioListenerComponent();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;


private:

	FMOD_VECTOR forward;
	FMOD_VECTOR up;

	FMOD_VECTOR pos;
	FMOD_VECTOR vel;
};




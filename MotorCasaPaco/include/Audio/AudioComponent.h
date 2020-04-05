#pragma once

#include "Entity/Component.h"
#include <fmod.hpp>
#include <fmod.h>
#include "Audio/AudioManager.h"

class AudioComponent : public Component
{
public:
	AudioComponent(json& args);
	~AudioComponent();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

	void removeEmisor();

private:
	int numObj = -1;
	FMOD_VECTOR pos;
	FMOD_VECTOR vel;
};




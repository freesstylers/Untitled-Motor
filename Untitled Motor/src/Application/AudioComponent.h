#pragma once

#include "Component.h"
#include <fmod.hpp>
#include <fmod.h>
#include "AudioManager.h"

class AudioComponent : public Component
{
public:
	AudioComponent(json& args);
	~AudioComponent();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

	void deleteComponent();

private:
	int numObj;
	FMOD_VECTOR pos;
	FMOD_VECTOR vel;
};




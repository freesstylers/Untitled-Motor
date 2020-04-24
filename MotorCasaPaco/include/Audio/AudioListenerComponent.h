#pragma once
#include "Entity/Component.h"
#include "Audio/AudioManager.h"
#include <OgreCamera.h>

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




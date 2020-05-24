#pragma once

#include "Entity/Component.h"
#include "Audio/AudioManager.h"
#include <string>

class AudioComponent : public Component
{
public:
	AudioComponent(json& args);
	~AudioComponent();
	bool ReceiveEvent(Event& event) override;
	void update() override;
	void init(json& args) override;

	virtual void playMusic(std::string path,int channel);
	virtual void playMusic(std::string path);

	void removeEmisor();

private:
	int numObj = -1;
	Vector3 pos;
	Vector3 vel;
	std::string audioRoute;
};




#pragma once

#include <iostream>
#include <array>

#include "Others/General.h"

namespace FMOD {
	class ChannelGroup;
	class Channel;
	class System;
}

enum FMOD_RESULT;

class AudioManager
{
public:

	struct emisor {
		Vector3 soundPos;
		Vector3	soundVel;
	};

	static AudioManager* getInstance();
	static bool setupInstance();
	static void clean();

	~AudioManager();

	void playSound(const char* path, int nChannel);
	void playMusic(const char* path, int nChannel);

	void pauseChannel(int nChannel);
	void setVolume(float vol, int nChannel);

	bool isPlaying();
	bool isPlayingChannel(int nChannel);

	void update();
	void updateListener(Vector3 position, Vector3 velocity, Vector3 forward, Vector3 up);
	void updateSound(Vector3 position, Vector3 velocity, int nChannel, int numObj);

	int addEmisor(Vector3 position, Vector3 velocity);
	void removeEmisor(int numObj);

private:
	AudioManager();

	FMOD::System* system;
	FMOD_RESULT result;

	emisor emisores[32];
	Vector3 listenerVelocity, listenerUp, listenerForward, listenerPos;
	bool activo[32];
	FMOD::ChannelGroup* channelGroup;
	FMOD::Channel* channels[32];

	static AudioManager* instance;

};


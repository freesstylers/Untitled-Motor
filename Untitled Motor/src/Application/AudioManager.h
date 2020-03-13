#pragma once
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include <iostream>

using namespace FMOD;
using namespace std;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void playSound(const char* path, int nChannel);
	void playMusic(const char* path, int nChannel);

	bool isPlaying();
	bool isPlayingChannel(int nChannel);
	void update();

private:
	FMOD::System* system;
	FMOD_RESULT result;
	FMOD::ChannelGroup* channelGroup;
	FMOD::Channel* channels[];

};


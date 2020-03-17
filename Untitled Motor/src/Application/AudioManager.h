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

private:
	AudioManager();

	FMOD::System* system;
	FMOD_RESULT result;

	FMOD::ChannelGroup* channelGroup;
	FMOD::Channel* channels[];

	static AudioManager* instance;

};


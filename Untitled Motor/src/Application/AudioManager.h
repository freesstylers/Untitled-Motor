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

	void playSound(const char* path, int nChannel, FMOD_VECTOR pos);
	void playMusic(const char* path, int nChannel);

	void pauseChannel(int nChannel);
	void setVolume(float vol, int nChannel);

	bool isPlaying();
	bool isPlayingChannel(int nChannel);

	void update();
	void updateListener(FMOD_VECTOR position, FMOD_VECTOR velocity, FMOD_VECTOR forward, FMOD_VECTOR up);
	void updateSound(FMOD_VECTOR position, FMOD_VECTOR velocity, int nChannel);

private:
	AudioManager();

	FMOD::System* system;
	FMOD_RESULT result;

	//FMOD_VECTOR* posEmisores[32];
	//FMOD_VECTOR* velEmisores[32];
	FMOD_VECTOR listenerVelocity, listenerUp, listenerForward, listenerPos, soundPos, soundVel; 
	bool activo[32];
	FMOD::ChannelGroup* channelGroup;
	FMOD::Channel* channels[];

	static AudioManager* instance;

};


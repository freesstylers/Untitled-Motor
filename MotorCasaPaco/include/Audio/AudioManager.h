#pragma once

#include <iostream>
#include <array>

#include "Others/General.h"


namespace FMOD 
{
	class ChannelGroup;
	class Channel;
	class System;

	namespace Studio
	{
		class System;
		class Bank;
		class EventDescription;
		class EventInstance;
	}
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

	//////////////////////

	void LoadBankFile();

	void playEvent(std::string event);
	void stopEvent(std::string event);

	void setEventParameter(std::string event, std::string parameter, float value);
	float getEventParameter(std::string event, std::string parameter, float value);

	//////////////////////

	void playSound(const char* path, int nChannel);
	void playMusic(const char* path, int nChannel,bool loop);

	void pauseChannel(int nChannel);
	void stopChannel(int nChannel);
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

	//Studio::System* studio;

	FMOD_RESULT result;

	emisor emisores[32];
	Vector3 listenerVelocity, listenerUp, listenerForward, listenerPos;
	bool activo[32];
	FMOD::ChannelGroup* channelGroup;
	FMOD::Channel* channels[32];

	static AudioManager* instance;

	/////////////

	FMOD::System* coreSystem;
	FMOD::Studio::System* system;
	FMOD::Studio::Bank* bank;

	FMOD::Studio::EventInstance* getEventInstance(std::string event);
	void startEvents();

	FMOD::Studio::EventDescription* MenuNivelesEvent;
	FMOD::Studio::EventInstance* MenuNivelesInstance;

	FMOD::Studio::EventDescription* InLevelEvent;
	FMOD::Studio::EventInstance* InLevelInstance;

};


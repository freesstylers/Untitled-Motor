#include "AudioManager.h"
#include <stdexcept>

AudioManager* AudioManager::instance = 0;

AudioManager::AudioManager() 
{
    
    system = nullptr;


    result = FMOD::System_Create(&system);      // Create the main system object.
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n"+ result + string(FMOD_ErrorString(result)));
    }

    channelGroup = nullptr;
    result = system->createChannelGroup("inGameSoundEffects", &channelGroup);
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    listenerVelocity.x = 1;
    listenerVelocity.y = 1;
    listenerVelocity.z = 1;
    listenerUp.x = 0.f;
    listenerUp.y = 1.f;
    listenerUp.z = 0;
    listenerForward.x = 0.f;
    listenerForward.y = 0.f;
    listenerForward.z = 1.0;
    listenerPos.x = 3.f;
    listenerPos.y = 3.f;
    listenerPos.z = 1.f;

    system->set3DSettings(10.0f, 10.0f, 10.0f);


}  

AudioManager* AudioManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool AudioManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new AudioManager();
		return true;
	}

	return false;
}

void AudioManager::clean()
{
	delete instance;
}

AudioManager::~AudioManager()
{
    channelGroup->release();
    system->release();
 

    //delete system;
    //delete channelGroup;

    //delete channels;
}

void AudioManager::setVolume(float vol, int nChannel)
{
    channels[nChannel]->setVolume(vol);
}

void AudioManager::pauseChannel(int nChannel)
{
    bool isPaused;
    channels[nChannel]->getPaused(&isPaused);
    if (isPaused)
    {
        channels[nChannel]->setPaused(false);
    }

    else if (!isPaused)
    {
        channels[nChannel]->setPaused(true);
    }
}

bool AudioManager::isPlaying()
{
    bool isPlaying;
    channelGroup->isPlaying(&isPlaying);
    return isPlaying;
}

void AudioManager::update() 
{
    if (isPlaying()) {
        system->update();
    }
}

bool AudioManager::isPlayingChannel(int nChannel)
{
    bool isPlaying;
    channels[nChannel]->isPlaying(&isPlaying);
    return isPlaying;
}


void AudioManager::playMusic(const char* path, int nChannel)
{
    Sound* sound;
    
    int i = 0;

   

    system->createSound(path, FMOD_CREATESTREAM, nullptr, &sound);


    result = system->playSound(sound, nullptr, false, &channels[nChannel]);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }
    result = channels[nChannel]->setChannelGroup(channelGroup);
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }
   
}

void AudioManager::updateListener(FMOD_VECTOR position, FMOD_VECTOR velocity, FMOD_VECTOR forward, FMOD_VECTOR up)
{

    listenerVelocity.x = velocity.x;
    listenerVelocity.y = velocity.y;
    listenerVelocity.z = velocity.z;

    listenerPos.x = position.x;
    listenerPos.y = position.y;
    listenerPos.z = position.z;

    listenerForward.x = forward.x;
    listenerForward.y = forward.y;
    listenerForward.z = forward.z;

    listenerUp.x = up.x;
    listenerUp.y = up.y;
    listenerUp.z = up.z;

    system->set3DListenerAttributes(0, &listenerPos, &listenerVelocity, &listenerForward, &listenerUp);

}

void AudioManager::updateSound(FMOD_VECTOR position, FMOD_VECTOR velocity, int nChannel)
{
    soundPos.x = position.x;
    soundPos.y = position.y;
    soundPos.z = position.z;

    soundVel.x = velocity.x;
    soundVel.y = velocity.y;
    soundVel.z = velocity.z;

    channels[nChannel]->set3DAttributes(&soundPos, &soundVel);
}

void AudioManager::playSound(const char* path, int nChannel, FMOD_VECTOR pos)
{

   Sound* sound;
   system->createSound(path, FMOD_DEFAULT, nullptr,  &sound);



   result = system->playSound(sound, nullptr, false, &channels[nChannel]);
   

   if (result != FMOD_OK)
   {
       throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
   }
   result = channels[nChannel]->setChannelGroup(channelGroup);
   if (result != FMOD_OK)
   {
       throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
   }
   
  
}
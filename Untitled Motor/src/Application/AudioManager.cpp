#include "AudioManager.h"
#include <stdexcept>

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
}  

AudioManager::~AudioManager()
{
    channelGroup->release();
    system->release();
 

    delete system;
    delete channelGroup;

    delete []channels;
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

void AudioManager::playSound(const char* path, int nChannel)
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
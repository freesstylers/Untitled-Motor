#include "Audio/AudioManager.h"
#include <stdexcept>
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include "checkML.h"

using namespace FMOD;
using namespace std;

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
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    channelGroup = nullptr;
    result = system->createChannelGroup("inGameSoundEffects", &channelGroup);
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    listenerVelocity.X = 1;
    listenerVelocity.Y = 1;
    listenerVelocity.Z = 1;
    listenerUp.X = 0.f;
    listenerUp.Y = 1.f;
    listenerUp.Z = 0;
    listenerForward.X = 0.f;
    listenerForward.Y = 0.f;
    listenerForward.Z = 1.0;
   
    for (int i = 0; i < 32 ; i++) {

        emisores->soundPos.X = 0;
        emisores->soundPos.Y = 0;
        emisores->soundPos.Z = 0;

        emisores->soundVel.X = 0;
        emisores->soundVel.Y = 0;
        emisores->soundVel.Z = 0;
    }

    for (int i = 0; i < 32; i++) {
        activo[i] = false;
    }
    system->set3DSettings(1.0f, 10.0f, 1.0f);


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
    //channelGroup->release();
    //system->release();
 
}

int AudioManager::addEmisor(Vector3 position, Vector3 velocity)
{
    int i = 0;

    while (activo[i]) {
        i++;
    }

    emisores[i].soundPos.X = position.X;
    emisores[i].soundPos.Y = position.Y;
    emisores[i].soundPos.Z = position.Z;

    emisores[i].soundVel.X = velocity.X;
    emisores[i].soundVel.Y = velocity.Y;
    emisores[i].soundVel.Z = velocity.Z;

    activo[i] = true;
    return i;
}

void AudioManager::removeEmisor(int numObj)
{
    activo[numObj] = false;
    emisores[numObj].soundPos.X = 0;
    emisores[numObj].soundPos.Y = 0;
    emisores[numObj].soundPos.Z = 0;

    emisores[numObj].soundVel.X = 0;
    emisores[numObj].soundVel.X = 0;
    emisores[numObj].soundVel.X = 0;
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

void AudioManager::updateListener(Vector3 position, Vector3 velocity, Vector3 forward, Vector3 up)
{

    listenerVelocity.X = velocity.X;
    listenerVelocity.Y = velocity.Y;
    listenerVelocity.Z = velocity.Z;

    listenerPos.X = position.X;
    listenerPos.Y = position.Y;
    listenerPos.Z = position.Z;

    listenerForward.X = forward.X;
    listenerForward.Y = forward.Y;
    listenerForward.Z = forward.Z;

    listenerUp.X = up.X;
    listenerUp.Y = up.Y;
    listenerUp.Z = up.Z;

    system->set3DListenerAttributes(0, &PacoToFMOD(listenerPos), &PacoToFMOD(listenerVelocity) , &PacoToFMOD(listenerForward) , &PacoToFMOD(listenerUp));

}

void AudioManager::updateSound(Vector3 position, Vector3 velocity, int nChannel, int numObj)
{
        emisores[numObj].soundPos.X = position.X;
        emisores[numObj].soundPos.Y = position.Y;
        emisores[numObj].soundPos.Z = position.Z;

        emisores[numObj].soundVel.X = velocity.X;
        emisores[numObj].soundVel.Y = velocity.Y;
        emisores[numObj].soundVel.Z = velocity.Z;
    

    channels[nChannel]->set3DAttributes(&PacoToFMOD(emisores[numObj].soundPos), &PacoToFMOD(emisores[numObj].soundVel));
}

void AudioManager::playSound(const char* path, int nChannel)
{

   Sound* sound;
   system->createSound(path, FMOD_3D_HEADRELATIVE, nullptr,  &sound);

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
#include "AudioManager.h"
#include <stdexcept>
AudioManager::AudioManager() 
{
    FMOD_RESULT result;
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
}

AudioManager::~AudioManager()
{
    delete system;
}

void AudioManager::playSound()
{
   FMOD_MODE soundMode = FMOD_LOOP_NORMAL;
   FMOD::Sound* sound = System::createSound(".\assets\sound\nice.mp3",soundMode,FMOD_CREATESOUNDEXINFO )
}
#include "Audio/AudioManager.h"
#include <stdexcept>
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include "checkML.h"
#include <fmod_studio.h>
#include <fmod_studio.hpp>

using namespace FMOD;
using namespace std;

AudioManager* AudioManager::instance = 0;

AudioManager::AudioManager() 
{
    
    system = nullptr;

    result = FMOD::Studio::System::create(&system);      // Create the main system object.
    
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    channelGroup = nullptr;
    
    //result = coreSystem->createChannelGroup("inGameSoundEffects", &channelGroup);
    
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = system->getCoreSystem(&coreSystem);
    
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
    
    coreSystem->set3DSettings(1.0f, 10.0f, 1.0f);

    result = system->loadBankFile("MUS/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);      // Create the main system object.
    
    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = system->loadBankFile("MUS/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);      // Create the main system object.

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = bank->loadSampleData();

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    startEvents();
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
    system->release();
    coreSystem->close();
    coreSystem->release();
    channelGroup->release();
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

void AudioManager::stopChannel(int nChannel)
{
     channels[nChannel]->stop();
}

bool AudioManager::isPlaying()
{
    bool isPlaying;
    channelGroup->isPlaying(&isPlaying);
    return isPlaying;

    return false;
}

void AudioManager::update() 
{
    system->update();
    if (isPlaying()) {
        system->update();
    }
}

bool AudioManager::isPlayingChannel(int nChannel)
{
    bool isPaused;
    channels[nChannel]->getPaused(&isPaused);
    return !isPaused;

    return false;
}


void AudioManager::playMusic(const char* path, int nChannel, bool loop)
{
    Sound* sound;

    coreSystem->createSound(path, FMOD_CREATESTREAM, nullptr, &sound);

    if (loop) {
        sound->setMode(FMOD_LOOP_NORMAL);
    }
    
    result = coreSystem->playSound(sound, nullptr, false, &channels[nChannel]);

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

    FMOD_VECTOR a = PacoToFMOD(listenerPos);
    FMOD_VECTOR b = PacoToFMOD(listenerVelocity);
    FMOD_VECTOR c = PacoToFMOD(listenerForward);
    FMOD_VECTOR d = PacoToFMOD(listenerUp);

    coreSystem->set3DListenerAttributes(0, &a, &b , &c , &d);

}

void AudioManager::updateSound(Vector3 position, Vector3 velocity, int nChannel, int numObj)
{
        emisores[numObj].soundPos.X = position.X;
        emisores[numObj].soundPos.Y = position.Y;
        emisores[numObj].soundPos.Z = position.Z;

        emisores[numObj].soundVel.X = velocity.X;
        emisores[numObj].soundVel.Y = velocity.Y;
        emisores[numObj].soundVel.Z = velocity.Z;
    
        FMOD_VECTOR a = PacoToFMOD(emisores[numObj].soundPos);
        FMOD_VECTOR b = PacoToFMOD(emisores[numObj].soundVel);


    channels[nChannel]->set3DAttributes(&a, &b);
}

void AudioManager::LoadBankFile()
{
    //studioSystem
    //FMOD::Studio::System::loadBankFile("eee");
}

void AudioManager::playEvent(std::string event)
{
    if (event == "MenuNiveles")
    {
        FMOD_STUDIO_PARAMETER_DESCRIPTION test;
        result = MenuNivelesEvent->getParameterDescriptionByName("NivelesCompletados", &test);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }

        MenuNivelesInstance->start();
    }
    else if (event == "InLevel")
    {
        FMOD_STUDIO_PARAMETER_DESCRIPTION test;
        //result = MenuNivelesEvent->getParameterDescriptionByName("NivelesCompletados", &test);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }

        InLevelInstance->start();
    }
    else
        return;
}

void AudioManager::stopEvent(std::string event)
{
    if (event == "MenuNiveles")
    {
        MenuNivelesInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
    }
    else if (event == "InLevel")
    {
        InLevelInstance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
    }
    else
        return;
}

void AudioManager::setEventParameter(std::string event, std::string parameter, float value)
{
    if (event == "MenuNiveles")
    {
        result = MenuNivelesInstance->setParameterByName(parameter.c_str(), value);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }
    }
    else if (event == "InLevel")
    {
        result = InLevelInstance->setParameterByName(parameter.c_str(), value);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }
    }
}

float AudioManager::getEventParameter(std::string event, std::string parameter, float value)
{
    if (event == "MenuNiveles")
    {
        result = MenuNivelesInstance->getParameterByName(parameter.c_str(), &value);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }

        return value;
    }
    else if (event == "InLevel")
    {
        result = InLevelInstance->getParameterByName(parameter.c_str(), &value);

        if (result != FMOD_OK)
        {
            throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
        }

        return value;
    }
}

FMOD::Studio::EventInstance* AudioManager::getEventInstance(std::string event)
{
    if (event == "MenuNiveles")
    {
        return MenuNivelesInstance;
    }
    else if (event == "InLevel")
    {
        return InLevelInstance;
    }
    else
        return nullptr;
}

void AudioManager::startEvents()
{
    result = system->getEvent("event:/MenuNiveles", &MenuNivelesEvent);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = MenuNivelesEvent->createInstance(&MenuNivelesInstance);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = system->getEvent("event:/InLevel", &InLevelEvent);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }

    result = InLevelEvent->createInstance(&InLevelInstance);

    if (result != FMOD_OK)
    {
        throw std::runtime_error("FMOD error! (%d) %s\n" + result + string(FMOD_ErrorString(result)));
    }
}

void AudioManager::playSound(const char* path, int nChannel)
{

   Sound* sound;
   coreSystem->createSound(path, FMOD_3D_HEADRELATIVE, nullptr,  &sound);

   result = coreSystem->playSound(sound, nullptr, false, &channels[nChannel]);
   

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
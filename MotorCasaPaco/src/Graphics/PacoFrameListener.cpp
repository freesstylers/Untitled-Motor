#include "Graphics/PacoFrameListener.h"

#include <OgreTimer.h>

#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Scene/SceneManager.h"
#include "Audio/AudioManager.h"
#include "Events/EventManager.h"
#include "GUI/GUI_Manager.h"
#include "MotorCasaPaco.h"

#include <Windows.h> 

#include <SDL_events.h>
#include "checkML.h"


PacoFrameListener::PacoFrameListener() : Ogre::FrameListener(), deltaTime_(0)
{
	timer_ = new Ogre::Timer();
	prevTime = std::chrono::high_resolution_clock::now();
}

PacoFrameListener::~PacoFrameListener()
{
	delete timer_; timer_ = nullptr;
}

bool PacoFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{

	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - prevTime;

	deltaTime_ = elapsed.count();

	prevTime = std::chrono::high_resolution_clock::now(); //Necesita Windows.h
	
	MotorCasaPaco::getInstance()->processFrame();

	return true;
}

//Devuleve los milisegundos que lleva activo el programa
uint64_t PacoFrameListener::getTime()
{
	return GetTickCount();
}

//Diferencia de tiempos en milisegundos
uint64_t PacoFrameListener::getTimeDifference(uint64_t prevTime)
{
	return getTime() - prevTime;
}

//Segundos que ha tardado un frame
double PacoFrameListener::DeltaTime()
{
	return deltaTime_;
}

void PacoFrameListener::resetTimer()
{
	timer_->reset();
}
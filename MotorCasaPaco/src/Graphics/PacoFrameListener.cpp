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

#include <SDL_events.h>
#include "checkML.h"

PacoFrameListener::PacoFrameListener() : Ogre::FrameListener(), deltaTime_(0)
{
	timer_ = new Ogre::Timer();
}

PacoFrameListener::~PacoFrameListener()
{
	delete timer_; timer_ = nullptr;
}

bool PacoFrameListener::frameStarted(const Ogre::FrameEvent& evt)
{
	float prevTime = getTime();
	
	MotorCasaPaco::getInstance()->processFrame();

	deltaTime_ = getTimeDifference(prevTime);

	return true;
}

float PacoFrameListener::getTime()
{
	return timer_->getMicroseconds() / 1000.0f;
}

float PacoFrameListener::getTimeDifference(float prevTime)
{
	return timer_->getMicroseconds() / 1000.0f - prevTime;
}

float PacoFrameListener::DeltaTime()
{
	return deltaTime_;
}

void PacoFrameListener::resetTimer()
{
	timer_->reset();
}
#pragma once

#include <OgreFrameListener.h>
#include "Graphics\PacoFrameListener.h"
#include <chrono>

namespace Ogre {
	class Timer;
}

class PacoFrameListener : public Ogre::FrameListener {
public:
	PacoFrameListener();
	~PacoFrameListener();

	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
	virtual void windowMoved(Ogre::RenderWindow* rw) {}
	virtual void windowResized(Ogre::RenderWindow* rw) {}
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	virtual void windowClosed(Ogre::RenderWindow* rw) {}
	virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

	double getTime();
	double getTimeDifference(double prevTime);
	double DeltaTime();
	void resetTimer();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> prevTime;
	double deltaTime_;
	Ogre::Timer* timer_;
};
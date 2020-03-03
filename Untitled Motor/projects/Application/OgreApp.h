#pragma once

#include <stdio.h>
#include <OgreRoot.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include "windows.h"
#include <iostream>
#include <fmod.hpp>
#include <btBulletDynamicsCommon.h>
#include <OgreApplicationContext.h>
#include <OgreRenderWindow.h>

using namespace OgreBites;

class OgreApp : public ApplicationContext {
public:
	OgreApp();

	void setup(void);
};

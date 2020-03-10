#pragma once
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include <iostream>

using namespace FMOD;
using namespace std;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void playSound();

private:
	FMOD::System* system;
	

};


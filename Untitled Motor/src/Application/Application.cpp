// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Entity.h"


#include <OgreException.h>
#include <iostream>
#include <stdexcept>

//#include <btBulletDynamicsCommon.h>
#define NOMINMAX

#include "windows.h"

#include "Core.h"



Core* core;

#ifdef  _DEBUG
    int main(int argc, char* argv[])
#else
    #include <Windows.h>
    int WINAPI
    WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{

	try { Core::setupInstance("Motor Casa Paco"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("Core init fail \n" + (Ogre::String)e.what() + "\n");	return;
	}

	core = Core::getInstance();

	SDL_Init(SDL_INIT_EVERYTHING);

	try
	{
		core->init();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		delete core;
		SDL_Quit();

		return 0;
	}


	core->changeScene("test");

	core->start();

	delete core;
	SDL_Quit();

    return 0;
}
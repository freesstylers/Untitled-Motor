// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <json.hpp>

#include <OgreException.h>
#include <iostream>
#include <stdexcept>
#define NOMINMAX



#include "windows.h"

#include "Core.h"


using json = nlohmann::json;
using namespace std;


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
			throw std::runtime_error("Core init fail \n" + (Ogre::String)e.what() + "\n");	return 0;
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


		core->changeScene("verticalSlice");

		core->start();

		delete core;

		SDL_Quit();

		return 0;
}
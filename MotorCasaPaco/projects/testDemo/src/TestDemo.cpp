#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "GUI/GUI_Manager.h"

MotorCasaPaco* motorCasaPaco;

#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try { MotorCasaPaco::setupInstance("Motor Casa Paco"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("Motor Casa Paco init fail \n" + std::string(e.what()) + "\n");	return 0;
	}

	motorCasaPaco = MotorCasaPaco::getInstance();

	try
	{
		motorCasaPaco->init();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		delete motorCasaPaco;
		return 0;
	}

	motorCasaPaco->changeScene("UITest");

	motorCasaPaco->start();

	delete motorCasaPaco;

	return 0;
}
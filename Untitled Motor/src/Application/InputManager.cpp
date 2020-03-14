#include "InputManager.h"
#include <iostream>

InputManager* InputManager::instance = 0;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	for (int i = 0; i < NumControls && controllers.size() > i; i++)
		SDL_GameControllerClose(controllers[i]);

	controllers.clear();
}

InputManager* InputManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool InputManager::setupInstance()
{
	if (instance == 0)
	{
		instance = new InputManager();
		return true;
	}

	return false;
}

void InputManager::clean()
{
	delete instance;
}

void InputManager::setup()
{
	//SetUp de Mandos con variable para numero de mandos
	for (int i = 0; i < NumControls; i++)
		controllers.push_back(SDL_GameControllerOpen(0));

	//Mapping de esquemas de controles?
}

void InputManager::InputManagement(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			KeyBoardInputManagement(event);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			GameControllerInputManagement(event);
			break;
		case SDL_CONTROLLERAXISMOTION:
			GameControllerAxisManagement(event);
			break;
		default:
			break;
	}
}

void InputManager::KeyBoardInputManagement(SDL_Event event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_DOWN:
		break;
	case SDLK_UP:
		break;
	case SDLK_LEFT:
		break;
	case SDLK_RIGHT:
		break;
	case SDLK_s:
		break;
	case SDLK_w:
		break;
	case SDLK_a:
		break;
	case SDLK_d:
		break;
	}
}

void InputManager::GameControllerInputManagement(SDL_Event event)
{
	if (SDL_GameControllerGetButton(controllers[event.cbutton.which], SDL_CONTROLLER_BUTTON_A))
		std::cout << "eeeee" << std::endl;

	//Esto no se como hacerlo con un switch para que tenga en cuenta que mando es, y que boton
}

void InputManager::GameControllerAxisManagement(SDL_Event event)
{
	//Esto ni zorra de como se hacia en SDL asi que que lo haga otro
}

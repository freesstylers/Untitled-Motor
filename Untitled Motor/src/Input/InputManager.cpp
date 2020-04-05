#include "Input/InputManager.h"
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
		controllers.push_back(SDL_GameControllerOpen(i));	
	//Mapping de esquemas de controles?
}

void InputManager::GeneralInputManagement(SDL_Event event)
{

	switch (event.type)
	{
		//En principio, como se puede preguntar si X tecla o boton del mando está pulsada/o, no hace falta gestionar esos eventos
		/*
		//Teclado
		case SDL_KEYDOWN:
			KeyBoardInputManagement(event);
			break;
		case SDL_KEYUP:
			KeyBoardInputManagement(event);
			break;
		//Mando
		case SDL_CONTROLLERBUTTONDOWN:
			//GameControllerInputManagement(event);
			break;
		case SDL_CONTROLLERBUTTONUP:
			//GameControllerInputManagement(event);
			break;
		case SDL_CONTROLLERAXISMOTION:
			//GameControllerAxisManagement(event);
			break;
		*/

		//Estos si hay que guardarlos
		//Raton
		case SDL_MOUSEMOTION:
			
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y != mouseWheel.y) // scroll up/down
			{
				MouseWheelChange(1, event.wheel.y);
			}
			else if (event.wheel.x != mouseWheel.x) // scroll left
			{
				MouseWheelChange(0, event.wheel.x);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			MouseButtonChange(event.button.button, 0);
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonChange(event.button.button, 1);
			break;
		default:
			break;
	}
}

bool InputManager::GameControllerIsButtonDown(SDL_GameControllerButton button, int controller)
{
	return (SDL_GameControllerGetButton(controllers[controller], button));
}

void InputManager::MouseButtonChange(int button, int change)
{
	switch (button)
	{
	case SDL_BUTTON_LEFT:
		if (change)
			mouseButtons.leftPressed = true;
		else
			mouseButtons.leftPressed = false;
		break;
	case SDL_BUTTON_RIGHT:
		if (change)
			mouseButtons.rightPressed = true;
		else
			mouseButtons.rightPressed = false;
		break;
	case SDL_BUTTON_MIDDLE:
		if (change)
			mouseButtons.middlePressed = true;
		else
			mouseButtons.middlePressed = false;
		break;
	default:
		break;
	}
}

void InputManager::MouseWheelChange(int field, int value)
{
	if (field)
		mouseWheel.y = value;
	else
		mouseWheel.x = value;
}

void InputManager::MousePositionChange(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

int InputManager::GameControllerGetAxisMovement(SDL_GameControllerAxis axis, int controller)
{
	return SDL_GameControllerGetAxis(controllers[controller], axis);
}

SDL_GameController* InputManager::getWhichController(SDL_Event event)
{
	if (event.type == (SDL_CONTROLLERBUTTONDOWN || SDL_CONTROLLERBUTTONUP))
	{
		return SDL_GameControllerFromInstanceID(event.cbutton.which);
	}
	else if (event.type == SDL_CONTROLLERAXISMOTION)
	{
		return SDL_GameControllerFromInstanceID(event.caxis.which);
	}
}

InputManager::MouseButtons InputManager::getMouseButtons()
{
	return mouseButtons;
}

InputManager::MousePosition InputManager::getMousePosition()
{
	return mousePosition;
}

InputManager::MouseWheel InputManager::getMouseWheel()
{
	return mouseWheel;
}

bool InputManager::IsKeyDown(SDL_Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	return state[key];
}
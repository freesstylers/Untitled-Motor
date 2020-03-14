#pragma once

#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>

class InputManager	//carga de recursos (por ahora)
{
public:
	~InputManager();

	static InputManager* getInstance();
	static bool setupInstance();
	static void clean();

	void setup();

	void InputManagement(SDL_Event event);

	void KeyBoardInputManagement(SDL_Event event);

	void GameControllerInputManagement(SDL_Event event);

	void GameControllerAxisManagement(SDL_Event event);
private:
	InputManager();

	std::vector<SDL_GameController*> controllers;
	
	const int NumControls = 1;

	static InputManager* instance;
};
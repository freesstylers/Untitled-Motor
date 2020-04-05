#pragma once

#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>

class InputManager	//carga de recursos (por ahora)
{

private:
	InputManager();

	static InputManager* instance;

	std::vector<SDL_GameController*> controllers;

	const int NumControls = 1;

	struct MouseButtons { bool leftPressed = false; bool middlePressed = false; bool rightPressed = false; } mouseButtons;
	struct MouseWheel { int x = 0; int y = 0; } mouseWheel;
	struct MousePosition { int x = 0; int y = 0; } mousePosition;

public:
	~InputManager();

	static InputManager* getInstance();
	static bool setupInstance();
	static void clean();

	void setup();

	void GeneralInputManagement(SDL_Event event);

	bool GameControllerIsButtonDown(SDL_GameControllerButton button, int controller = 0);

	bool IsKeyDown(SDL_Scancode key);

	void MouseButtonChange(int button, int change);

	void MouseWheelChange(int field, int value);

	void MousePositionChange(int x, int y);

	int GameControllerGetAxisMovement(SDL_GameControllerAxis axis, int controller = 0);

	SDL_GameController* getWhichController(SDL_Event event);

	MouseButtons getMouseButtons();

	MouseWheel getMouseWheel();

	MousePosition getMousePosition();
};
#pragma once

#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>
#include <CEGUI/CEGUI.h>

class InputManager	//carga de recursos (por ahora)
{

private:
	struct ControllerToKey {
		SDL_Keycode A=SDLK_INSERT;
		SDL_Keycode B=SDLK_RETURN;
		SDL_Keycode X;
		SDL_Keycode Y;
		SDL_Keycode Start=SDLK_ESCAPE;
		SDL_Keycode Select;
		SDL_Keycode Left=SDLK_LEFT;
		SDL_Keycode Right=SDLK_RIGHT;
		SDL_Keycode Up=SDLK_UP;
		SDL_Keycode Down = SDLK_DOWN;
		SDL_Keycode LBump;
		SDL_Keycode RBump;
		SDL_Keycode LTrigg;
		SDL_Keycode RTrigg;
	};

	struct Controller {
		SDL_GameController* cReference=nullptr;
		bool initialised = false;
		float deadZoneRX=0;
		float deadZoneRY=0;
		float deadZoneLX=0;
		float deadZoneLY=0;
	};

	InputManager();

	static InputManager* instance;

	std::vector<Controller> controllers;

	ControllerToKey cKeyMapping;

	const int NumControls = 1;

	struct MouseButtons { bool leftPressed = false; bool middlePressed = false; bool rightPressed = false; } mouseButtons;
	struct MouseWheel { int x = 0; int y = 0; } mouseWheel;
	struct MousePosition { int x = 0; int y = 0; } mousePosition;

	float controllerdeadZoneRange=0.1;

	void InjectCEGUIInput(SDL_Event event);

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

	float GameControllerGetAxisMovement(SDL_GameControllerAxis axis, bool accel, int controller = 0);

	SDL_GameController* getWhichController(SDL_Event event);

	MouseButtons getMouseButtons();

	MouseWheel getMouseWheel();

	MousePosition getMousePosition();

	CEGUI::Key::Scan SDL_TO_CEGUI(SDL_Keycode key);
};
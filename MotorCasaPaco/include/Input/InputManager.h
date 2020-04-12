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
		SDL_Keycode Back=SDLK_TAB;
		SDL_Keycode Left=SDLK_LEFT;
		SDL_Keycode Right=SDLK_RIGHT;
		SDL_Keycode Up=SDLK_UP;
		SDL_Keycode Down = SDLK_DOWN;
		SDL_Keycode LBump=SDLK_q;
		SDL_Keycode RBump=SDLK_e;
		SDL_Keycode LTrigg=SDLK_1;
		SDL_Keycode RTrigg=SDLK_2;
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

	//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
	/*struct MouseButtons { bool leftPressed = false; bool middlePressed = false; bool rightPressed = false; } mouseButtons;
	struct MousePosition { int x = 0; int y = 0; } mousePosition;*/

	struct MouseWheel { int x = 0; int y = 0; } mouseWheel;

	float controllerdeadZoneRange=0.1;

	void InjectCEGUIInput(SDL_Event event);

	int joystickPressedX = 0;
	int joystickPressedY = 0;
	int LtriggerPressed = 0;
	int RtriggerPressed = 0;

public:
	~InputManager();

	static InputManager* getInstance();
	static bool setupInstance();
	static void clean();

	void setup();

	void GeneralInputManagement(SDL_Event event);

	bool GameControllerIsButtonDown(SDL_GameControllerButton button, int controller = 0);

	bool IsKeyDown(SDL_Scancode key);

	void MouseWheelChange(int field, int value);

	//void MousePositionChange(int x, int y);

	float GameControllerGetAxisMovement(SDL_GameControllerAxis axis, bool accel, int controller = 0);

	SDL_GameController* getWhichController(SDL_Event event);

	//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
	/*MouseButtons getMouseButtons();
	MousePosition getMousePosition();
	void MouseButtonChange(int button, int change);*/

	MouseWheel getMouseWheel();


	CEGUI::Key::Scan SDL_KeyCode_TO_CEGUI(SDL_Keycode key);
	CEGUI::MouseButton SDLMouseButtonToCEGUIMouseButton(Uint8 MouseButtons);
};
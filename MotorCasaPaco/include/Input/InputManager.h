#pragma once

#include <vector>
#include "Input/PacoKeys.h"

union SDL_Event;
struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

class InputManager	//carga de recursos (por ahora)
{

private:
	struct ControllerToKey {
		Keycode A=K_INSERT;
		Keycode B=K_RETURN;
		Keycode X;
		Keycode Y;
		Keycode Start=K_ESCAPE;
		Keycode Back=K_TAB;
		Keycode Left=K_LEFT;
		Keycode Right=K_RIGHT;
		Keycode Up=K_UP;
		Keycode Down = K_DOWN;
		Keycode LBump=K_q;
		Keycode RBump=K_e;
		Keycode LTrigg=K_1;
		Keycode RTrigg=K_2;
	};

	struct PacoController {
		SDL_GameController* cReference=nullptr;
		bool initialised = false;
		float deadZoneRX=0;
		float deadZoneRY=0;
		float deadZoneLX=0;
		float deadZoneLY=0;
	};

	InputManager();

	static InputManager* instance;

	std::vector<PacoController> controllers;

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

	bool GameControllerIsButtonDown(GameControllerButton button, int controller = 0);

	bool IsKeyDown(Scancode key);

	void MouseWheelChange(int field, int value);

	//void MousePositionChange(int x, int y);

	float GameControllerGetAxisMovement(GameControllerAxis axis, bool accel, int controller = 0);

	SDL_GameController* getWhichController(SDL_Event event);

	//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
	/*MouseButtons getMouseButtons();
	MousePosition getMousePosition();
	void MouseButtonChange(int button, int change);*/

	MouseWheel getMouseWheel();
};
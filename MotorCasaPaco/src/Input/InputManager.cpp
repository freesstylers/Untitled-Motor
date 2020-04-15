#include "Input/InputManager.h"
#include <iostream>

#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include <Vector>
#include <SDL_gamecontroller.h>
#include <SDL_events.h>
#include <CEGUI/CEGUI.h>
#include "checkML.h"

InputManager* InputManager::instance = 0;

CEGUI::Key::Scan KeyCode_TO_CEGUI(Keycode key)
{
	using namespace CEGUI;
	switch (key)
	{
	case K_UP:
		return Key::ArrowUp;
	case K_DOWN:
		return Key::ArrowDown;
	case K_LEFT:
		return Key::ArrowLeft;
	case K_RIGHT:
		return Key::ArrowRight;
	case K_ESCAPE:
		return Key::Escape;
	case K_INSERT:
		return Key::Insert;
	case K_SPACE:
		return Key::Space;
	default:
		return Key::Unknown;
	}
}

CEGUI::MouseButton MouseButtonToCEGUIMouseButton(Uint8 MouseButtons)
{
	switch (MouseButtons) {
	case BUTTON_LEFT: return CEGUI::MouseButton::LeftButton;
	case BUTTON_MIDDLE: return CEGUI::MouseButton::MiddleButton;
	case BUTTON_RIGHT: return CEGUI::MouseButton::RightButton;
	case BUTTON_X1: return CEGUI::MouseButton::X1Button;
	case BUTTON_X2: return CEGUI::MouseButton::X2Button;
	}
	return CEGUI::MouseButton::NoButton;
}

InputManager::InputManager()
{

}

void InputManager::InjectCEGUIInput(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI((Keycode)event.key.keysym.sym));
	}
	else if (event.type == SDL_KEYUP) {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI((Keycode)event.key.keysym.sym));
	}
	else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.A));
			break;
		case SDL_CONTROLLER_BUTTON_B:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.B));
			break;
		case SDL_CONTROLLER_BUTTON_X:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.X));
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Y));
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Back));
			break;
		case SDL_CONTROLLER_BUTTON_START:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Start));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Up));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Down));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Left));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Right));
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.LBump));
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.RBump));
			break;
		default:
			break;
		}

	}
	else if (event.type == SDL_CONTROLLERBUTTONUP) {
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.A));
			break;
		case SDL_CONTROLLER_BUTTON_B:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.B));
			break;
		case SDL_CONTROLLER_BUTTON_X:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.X));
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Y));
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Back));
			break;
		case SDL_CONTROLLER_BUTTON_START:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Start));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Up));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Down));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Left));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Right));
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.LBump));
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.RBump));
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_CONTROLLERAXISMOTION) {
		float x = GameControllerGetAxisMovement((GameControllerAxis)event.caxis.axis, false);
		switch ((SDL_GameControllerAxis)event.caxis.axis) {
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
			if (x != 0 && !LtriggerPressed) {
				LtriggerPressed = 1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.LTrigg));
			}
			else if (x == 0 && LtriggerPressed) {
				LtriggerPressed = 0;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.LTrigg));
			}
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
			if (x != 0 && !RtriggerPressed) {
				RtriggerPressed = 1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.RTrigg));
			}
			else if (x == 0 && RtriggerPressed) {
				RtriggerPressed = 0;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.RTrigg));
			}
			break;
		case SDL_CONTROLLER_AXIS_LEFTX:
			if (x > 0.2 && joystickPressedX < 1) {
				if (joystickPressedX != 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Left));
				}
				joystickPressedX = 1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Right));
			}
			else if (x < -0.2 && joystickPressedX > -1) {
				if (joystickPressedX != 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Right));
				}
				joystickPressedX = -1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Left));
			}
			else if (joystickPressedX != 0 && x > -0.2 && x < 0.2) {
				if (joystickPressedX > 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Right));
				}
				else {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Left));
				}
				joystickPressedX = 0;
			}
			break;
		case SDL_CONTROLLER_AXIS_LEFTY:
			if (x > 0.2 && joystickPressedY < 1) {
				if (joystickPressedY != 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Up));
				}
				joystickPressedY = 1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Down));
			}
			else if (x < -0.2 && joystickPressedY > -1) {
				if (joystickPressedY != 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Down));
				}
				joystickPressedX = -1;
				CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(KeyCode_TO_CEGUI(cKeyMapping.Up));
			}
			else if (joystickPressedY != 0 && x >-0.2 && x<0.2 ) {
				if (joystickPressedY > 0) {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Down));
				}
				else {
					CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(KeyCode_TO_CEGUI(cKeyMapping.Up));
				}
				joystickPressedY = 0;
			}
			break;
		default:
			break;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(MouseButtonToCEGUIMouseButton(event.button.button));
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(MouseButtonToCEGUIMouseButton(event.button.button));
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(event.motion.x, event.motion.y);
	}
}

InputManager::~InputManager()
{
	for (int i = 0; i < NumControls && controllers.size() > i; i++) {
		SDL_GameControllerClose(controllers[i].cReference);
	}
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
	for (int i = 0; i < NumControls; i++) {
		Controller c{ SDL_GameControllerOpen(i), 0, 0, 0, 0, false };
		controllers.push_back(c);
		controllers.back().deadZoneLX = GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTX, i);
		controllers.back().deadZoneLY = GameControllerGetAxisMovement(CONTROLLER_AXIS_LEFTY, i);
		controllers.back().deadZoneRX = GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTX, i);
		controllers.back().deadZoneRY = GameControllerGetAxisMovement(CONTROLLER_AXIS_RIGHTY, i);
		controllers.back().initialised = true;
	}
	//Mapping de esquemas de controles?
}

void InputManager::GeneralInputManagement(SDL_Event event)
{

	switch (event.type)
	{
		//En principio, como se puede preguntar si X tecla o boton del mando está pulsada/o, no hace falta gestionar esos eventos
		
		//Teclado
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

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT: 
				break;
			case SDL_BUTTON_MIDDLE: 
				break;
			case SDL_BUTTON_RIGHT: 
				break;
			case SDL_BUTTON_X1: 
				break;
			case SDL_BUTTON_X2: 
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button) {
			case SDL_BUTTON_LEFT:
				break;
			case SDL_BUTTON_MIDDLE:
				break;
			case SDL_BUTTON_RIGHT:
				break;
			case SDL_BUTTON_X1:
				break;
			case SDL_BUTTON_X2:
				break;
			}
			break;
		default:
			break;
	}

	InjectCEGUIInput(event);
}

bool InputManager::GameControllerIsButtonDown(GameControllerButton button, int controller)
{
	return (SDL_GameControllerGetButton(controllers[controller].cReference, (SDL_GameControllerButton)button));
}

//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
/*
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
}*/

void InputManager::MouseWheelChange(int field, int value)
{
	if (field)
		mouseWheel.y = value;
	else
		mouseWheel.x = value;
}

//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
/*
void InputManager::MousePositionChange(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}*/

float InputManager::GameControllerGetAxisMovement(GameControllerAxis axis, bool accel, int controller)
{
	Controller c = controllers[controller];

	float axisMax = (float)SDL_JOYSTICK_AXIS_MAX;
	float x = (float) SDL_GameControllerGetAxis(controllers[controller].cReference, (SDL_GameControllerAxis)axis);
	x = x / axisMax;

	if (!c.initialised || axis==SDL_CONTROLLER_AXIS_TRIGGERLEFT || axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
		return x;
	
	switch ((SDL_GameControllerAxis)axis)
	{
	case SDL_CONTROLLER_AXIS_LEFTX:
		if (x <= c.deadZoneLX + controllerdeadZoneRange && x >= c.deadZoneLX - controllerdeadZoneRange)
			x = 0;
		if (accel) {
			if (x < 0) x = x * x * -1;
			else x = x * x;
		}
		break;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		if (x <= c.deadZoneRX + controllerdeadZoneRange && x >= c.deadZoneRX - controllerdeadZoneRange)
			x = 0;
		if (accel) {
			if (x < 0) x = x * x * -1;
			else x = x * x;
		}
		break;
	case SDL_CONTROLLER_AXIS_LEFTY:
		if (x <= c.deadZoneLY + controllerdeadZoneRange && x >= c.deadZoneLY - controllerdeadZoneRange)
			x = 0;
		if (accel) {
			if (x < 0) x = x * x * -1;
			else x = x * x;
		}
		break;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		if (x <= c.deadZoneRY + controllerdeadZoneRange && x >= c.deadZoneRY - controllerdeadZoneRange)
			x = 0;
		if (accel) {
			if (x < 0) x = x * x * -1;
			else x = x * x;
		}
		break;
	default:
		break;
	}
	return x;

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

//Al final he encontrado forma de hacer esto con SDL, asi que puerta de momento
/*InputManager::MouseButtons InputManager::getMouseButtons()
{
	return mouseButtons;
}

InputManager::MousePosition InputManager::getMousePosition()
{
	return mousePosition;
}*/

InputManager::MouseWheel InputManager::getMouseWheel()
{
	return mouseWheel;
}

bool InputManager::IsKeyDown(Scancode key)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	return state[(SDL_Scancode)key];
}
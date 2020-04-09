#include "Input/InputManager.h"
#include <iostream>

InputManager* InputManager::instance = 0;

InputManager::InputManager()
{

}

void InputManager::InjectCEGUIInput(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN) {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(event.key.keysym.sym));
	}
	else if (event.type == SDL_KEYUP) {
		CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(event.key.keysym.sym));
	}
	else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.A));
			break;
		case SDL_CONTROLLER_BUTTON_B:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.B));
			break;
		case SDL_CONTROLLER_BUTTON_START:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.Start));
		break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.Up));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.Down));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.Left));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(SDL_TO_CEGUI(cKeyMapping.Right));
			break;
		default:
			break;
		}

	}
	else if (event.type == SDL_CONTROLLERBUTTONUP) {
		switch (event.cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.A));
			break;
		case SDL_CONTROLLER_BUTTON_B:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.B));
			break;
		case SDL_CONTROLLER_BUTTON_START:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.Start));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.Up));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.Down));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.Left));
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(SDL_TO_CEGUI(cKeyMapping.Right));
			break;
		default:
			break;
		}
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
		Controller c{ SDL_GameControllerOpen(i) };
		controllers.push_back(c);
		c.deadZoneLX = GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTX, i);
		c.deadZoneLY = GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_LEFTY, i);
		c.deadZoneRX = GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTX, i);
		c.deadZoneRY = GameControllerGetAxisMovement(SDL_CONTROLLER_AXIS_RIGHTY, i);
		c.initialised = true;
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
		case SDL_MOUSEBUTTONUP:
			MouseButtonChange(event.button.button, 0);
			break;
		case SDL_MOUSEBUTTONDOWN:
			MouseButtonChange(event.button.button, 1);
			break;
		default:
			InjectCEGUIInput(event);
			break;
	}
}

bool InputManager::GameControllerIsButtonDown(SDL_GameControllerButton button, int controller)
{
	return (SDL_GameControllerGetButton(controllers[controller].cReference, button));
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

float InputManager::GameControllerGetAxisMovement(SDL_GameControllerAxis axis, bool accel, int controller)
{
	Controller c = controllers[controller];
	
	float axisMax = (float)SDL_JOYSTICK_AXIS_MAX;
	float x = (float) SDL_GameControllerGetAxis(controllers[controller].cReference, axis);
	x = x / axisMax;

	if (!c.initialised)
		return x;
	
	switch (axis)
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

InputManager::MouseButtons InputManager::getMouseButtons()
{
	return mouseButtons;
}

InputManager::MousePosition InputManager::getMousePosition()
{
	return mousePosition;
}

CEGUI::Key::Scan InputManager::SDL_TO_CEGUI(SDL_Keycode key)
{
		using namespace CEGUI;
		switch (key)
		{
		case SDLK_UP:		
			return Key::ArrowUp;
		case SDLK_DOWN:          
			return Key::ArrowDown;
		case SDLK_LEFT:       
			return Key::ArrowLeft;
		case SDLK_RIGHT:        
			return Key::ArrowRight;
		case SDLK_ESCAPE:       
			return Key::Escape;
		case SDLK_INSERT:       
			return Key::Insert;
		case SDLK_SPACE:        
			return Key::Space;
		default:				
			return Key::Unknown;
		}
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
#include "MenuControllerInputComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"

MenuControllerInputComponent::MenuControllerInputComponent(json& args): Component(args)
{

}

MenuControllerInputComponent::~MenuControllerInputComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool MenuControllerInputComponent::function(const CEGUI::EventArgs& e)
{
	return true;
}

bool MenuControllerInputComponent::ReceiveEvent(Event& event)
{
	return false;
}

void MenuControllerInputComponent::update()
{
	posX += InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) * 10;
	posY += InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) * 10;
	MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(posX, posY);

	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A))
	{
		MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
	}
	else
	{
		MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
	}
}

void MenuControllerInputComponent::init(json& j)
{
	if (!j["buttons"].is_null() && j["buttons"].is_array())
	{
		std::vector<std::string> vec = j["buttons"];

		for (std::string name : vec) {

			int i = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getPosX();
			int j = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getPosY();
			
			posX = MotorCasaPaco::getInstance()->getScreenWidth()/2;
			posY = MotorCasaPaco::getInstance()->getScreenHeight()/2;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(posX, posY);

			std::cout << i << " " << j << "\n";
		}
	}
}

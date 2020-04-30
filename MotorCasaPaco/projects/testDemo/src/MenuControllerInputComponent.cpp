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
	//posX += InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) * 10;
	//posY += InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) * 10;
	//MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(posX, posY);

	if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT))
	{
		if (currenPos > 0)
			currenPos--;
		else
			currenPos = tam - 1;

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);

	}
	else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_RIGHTX, true) || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		if (currenPos < (tam - 1))
			currenPos++;
		else
			currenPos = 0;

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);

	}

	//Boton A
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
		
		int count = 0;
		
		for (std::string name : vec) {

			float i = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			float j = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();
			
			positionsX.push_back(i);
			positionsY.push_back(j);

			count++;
		}

		tam = count;
		currenPos = tam / 2;

		std::cout << tam << "\n";
		//posX = MotorCasaPaco::getInstance()->getScreenWidth() / 2;
		//posY = MotorCasaPaco::getInstance()->getScreenHeight() / 2;

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
	}
}

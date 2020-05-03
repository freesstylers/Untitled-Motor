#include "MainMenuInputComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"

MainMenuInputComponent::MainMenuInputComponent(json& args): Component(args)
{

}

MainMenuInputComponent::~MainMenuInputComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool MainMenuInputComponent::function(const CEGUI::EventArgs& e)
{
	return true;
}

bool MainMenuInputComponent::ReceiveEvent(Event& event)
{
	return false;
}

void MainMenuInputComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
		{
			if (currenPos > 0)
				currenPos--;
			else
				currenPos = tam - 1;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
		{
			if (currenPos < (tam - 1))
				currenPos++;
			else
				currenPos = 0;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
	}

		//Boton A
		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
	//}
}

void MainMenuInputComponent::init(json& j)
{
	if (!j["buttons"].is_null() && j["buttons"].is_array() && !j["delay"].is_null())
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

		delay = j["delay"];
		currentTime = MotorCasaPaco::getInstance()->getTime();

		tam = count;
		currenPos = tam / 2;
		
		std::cout << tam << "\n";
		//posX = MotorCasaPaco::getInstance()->getScreenWidth() / 2;
		//posY = MotorCasaPaco::getInstance()->getScreenHeight() / 2;

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
	}
}

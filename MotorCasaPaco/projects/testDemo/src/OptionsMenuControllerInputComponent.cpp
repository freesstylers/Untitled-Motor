#include "OptionsMenuControllerInputComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"

OptionsMenuControllerInputComponent::OptionsMenuControllerInputComponent(json& args): Component(args)
{

}

OptionsMenuControllerInputComponent::~OptionsMenuControllerInputComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool OptionsMenuControllerInputComponent::function(const CEGUI::EventArgs& e)
{
	return true;
}

bool OptionsMenuControllerInputComponent::ReceiveEvent(Event& event)
{
	return false;
}

void OptionsMenuControllerInputComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT))
		{
			if (where == 2)
			{
				if (currentXTopButtons == 0)
				{
					currentXTopButtons++;
				}
				else
				{
					currentXTopButtons--;
				}

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
			else if (where == 0)
			{
				if (currentPosDownButtons == 0)
					currentPosDownButtons = tamDownButtons - 1;
				else
					currentPosDownButtons--;

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXDownButtons[currentPosDownButtons], yDownButtons);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			if (where == 2)
			{
				if (currentXTopButtons == 0)
				{
					currentXTopButtons++;
				}
				else
				{
					currentXTopButtons--;
				}

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
			else if (where == 0)
			{
				if (currentPosDownButtons < 2)
					currentPosDownButtons++;
				else
					currentPosDownButtons = 0;

				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXDownButtons[currentPosDownButtons], yDownButtons);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}

			//MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			//currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_DOWN))
		{
			if (where == 2)
			{
				if (currentYTopButtons > 0) //Sigue en los botones de arriba
				{
					currentYTopButtons--;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
				else //Baja a los botones de abajo
				{
					where--;
					currentYTopButtons = 0;
					currentXTopButtons = 0;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtra, yExtra); //Extra Button
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}
			else if (where == 1)
			{
				where--;
				currentPosDownButtons = 1;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXDownButtons[currentPosDownButtons], yDownButtons);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
			else if (where == 0)
			{
				where = 2;
				currentYTopButtons = tamTopButtons - 1;
				currentXTopButtons = 0;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_UP))
		{
			if (where == 2)
			{
				if (currentYTopButtons < tamTopButtons - 1) //Sigue en los botones de arriba
				{
					currentYTopButtons++;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
				else //Baja a los botones de abajo
				{
					where = false;
					currentPosDownButtons = 1;
					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXDownButtons[currentPosDownButtons], yDownButtons);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}
			else if (where == 1)
			{
				where++;
				currentYTopButtons = 0;
				currentXTopButtons = 0;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXTopButtons[currentXTopButtons], positionsYTopButtons[currentYTopButtons]);
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
			else if (where == 0)
			{
				where++;
				currentYTopButtons = 0;
				currentXTopButtons = 0;
				MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xExtra, yExtra); //Extra Button
				currentTime = MotorCasaPaco::getInstance()->getTime();
			}
		}
	//}	

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
}

void OptionsMenuControllerInputComponent::init(json& j)
{
	if (!j["DownButtons"].is_null() && j["DownButtons"].is_array() && !j["delay"].is_null() && !j["TopButtons"].is_null() && j["TopButtons"].is_array())
	{
		std::vector<std::string> vec = j["DownButtons"];
		
		float y;

		for (std::string name : vec) 
		{
			float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();
			
			positionsXDownButtons.push_back(x);

			tamDownButtons++;
		}

		yDownButtons = y;

		std::vector<std::string> vec2 = j["TopButtons"];

		int count = 0;

		for (std::string name : vec2)
		{	
			if (count < 2)
			{
				float x = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
				positionsXTopButtons.push_back(x);
			}

			if (count % 2 == 0)
			{
				y = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

				positionsYTopButtons.push_back(y);
			}
			count++;
		}

		tamTopButtons = count/2;
		delay = j["delay"];

		std::string name = j["extraButton"];
		xExtra = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
		yExtra = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();

		currentTime = MotorCasaPaco::getInstance()->getTime();

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsXDownButtons[currentPosDownButtons], yDownButtons);
	}
}

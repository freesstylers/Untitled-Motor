#include "MenuControllerInputComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

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
}

void MenuControllerInputComponent::init(json& j)
{
	if (!j["buttons"].is_null() && j["buttons"].is_array())
	{
		std::vector<std::string> vec = j["buttons"];

		for (std::string name : vec) {

			int i = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getPosX();
			int j = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getPosY();

			std::cout << i << " " << j << "\n";
		}
	}
}

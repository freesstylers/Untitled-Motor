#include "ChangeFullScreenComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

ChangeFullScreenComponent::ChangeFullScreenComponent(json& args): Component(args)
{

}

ChangeFullScreenComponent::~ChangeFullScreenComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool ChangeFullScreenComponent::function(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getFullScreen())
	{ 
		MotorCasaPaco::getInstance()->setFullScreen(false);
		GUI_Manager::getInstance()->changeText(textToChange, "No");
	}
	else
	{ 
		MotorCasaPaco::getInstance()->setFullScreen(true);
		GUI_Manager::getInstance()->changeText(textToChange, "Si");
	}

	AudioManager::getInstance()->playSound("assets/sound/buttonSound.mp3", 0);

	return true;
}

bool ChangeFullScreenComponent::ReceiveEvent(Event& event)
{
	if (event.type == "RESET_GRAPHIC_INFO") {
		if (MotorCasaPaco::getInstance()->getFullScreen())
		{
			GUI_Manager::getInstance()->changeText(textToChange, "Si");
		}
		else
		{
			GUI_Manager::getInstance()->changeText(textToChange, "No");
		}
	}
	return false;
}

void ChangeFullScreenComponent::init(json& j)
{
	if (!j["button_1_Name"].is_null() && !j["button_2_Name"].is_null() && !j["textToChange"].is_null())
	{
		auto helperFunction = std::bind(&ChangeFullScreenComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_1_Name"]), helperFunction);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_2_Name"]), helperFunction);
		textToChange = GUI_Manager::getInstance()->getStaticText(j["textToChange"]);

		if (MotorCasaPaco::getInstance()->getFullScreen())
		{
			GUI_Manager::getInstance()->changeText(textToChange, "Si");
		}
		else
		{
			GUI_Manager::getInstance()->changeText(textToChange, "No");
		}

		EventManager::getInstance()->RegisterListener(this, "RESET_GRAPHIC_INFO");
	}
}

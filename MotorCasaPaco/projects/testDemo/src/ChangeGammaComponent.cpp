#include "ChangeGammaComponent.h"
#include "MotorCasaPaco.h"

ChangeGammaComponent::ChangeGammaComponent(json& args): Component(args)
{

}

ChangeGammaComponent::~ChangeGammaComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool ChangeGammaComponent::function(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getGamma())
	{ 
		MotorCasaPaco::getInstance()->setGamma(false);
		GUI_Manager::getInstance()->changeText(textToChange, "No");
	}
	else
	{ 
		MotorCasaPaco::getInstance()->setGamma(true);
		GUI_Manager::getInstance()->changeText(textToChange, "Si");
	}

	return true;
}

bool ChangeGammaComponent::ReceiveEvent(Event& event)
{
	if (event.type == EventType::RESET_GRAPHIC_INFO) {
		if (MotorCasaPaco::getInstance()->getGamma())
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

void ChangeGammaComponent::init(json& j)
{
	if (!j["button_More"].is_null() && !j["button_Less"].is_null() && !j["textToChange"].is_null())
	{
		auto helperFunction = std::bind(&ChangeGammaComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_More"]), helperFunction);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_Less"]), helperFunction);
		textToChange = GUI_Manager::getInstance()->getStaticText(j["textToChange"]);

		if (MotorCasaPaco::getInstance()->getGamma())
		{
			GUI_Manager::getInstance()->changeText(textToChange, "Si");
		}
		else
		{
			GUI_Manager::getInstance()->changeText(textToChange, "No");
		}

		EventManager::getInstance()->RegisterListener(this, EventType::RESET_GRAPHIC_INFO);

	}
}

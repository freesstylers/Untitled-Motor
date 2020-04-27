#include "ChangeVyncComponent.h"
#include "MotorCasaPaco.h"

ChangeVSyncComponent::ChangeVSyncComponent(json& args): Component(args)
{

}

ChangeVSyncComponent::~ChangeVSyncComponent()
{
	Component::~Component();
}

bool ChangeVSyncComponent::function(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getVSync())
	{ 
		MotorCasaPaco::getInstance()->setVSync(false);
		GUI_Manager::getInstance()->changeText(textToChange, "No");
	}
	else
	{ 
		MotorCasaPaco::getInstance()->setVSync(true);
		GUI_Manager::getInstance()->changeText(textToChange, "Si");
	}

	return true;
}

void ChangeVSyncComponent::init(json& j)
{
	if (!j["button_1_Name"].is_null() && !j["button_2_Name"].is_null() && !j["textToChange"].is_null())
	{
		auto helperFunction = std::bind(&ChangeVSyncComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_1_Name"]), helperFunction);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_2_Name"]), helperFunction);
		textToChange = GUI_Manager::getInstance()->getStaticText(j["textToChange"]);

		if (MotorCasaPaco::getInstance()->getVSync())
		{
			GUI_Manager::getInstance()->changeText(textToChange, "Si");
		}
		else
		{
			GUI_Manager::getInstance()->changeText(textToChange, "No");
		}
	}
}

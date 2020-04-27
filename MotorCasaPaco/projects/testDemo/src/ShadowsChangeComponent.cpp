#include "ShadowsChangeComponent.h"
#include "MotorCasaPaco.h"

ShadowsChangeComponent::ShadowsChangeComponent(json& args): Component(args)
{

}

ShadowsChangeComponent::~ShadowsChangeComponent()
{
	Component::~Component();
}

bool ShadowsChangeComponent::functionMore(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getShadows() == "Alto")
	{
		currenPos = 0;
	}
	else
	{
		currenPos++;
	}

	MotorCasaPaco::getInstance()->setShadows(values[currenPos]);
	GUI_Manager::getInstance()->changeText(textToChange, values[currenPos]);


	return true;
}

bool ShadowsChangeComponent::functionLess(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getShadows() == "No")
	{
		currenPos = 3;
	}
	else
	{
		currenPos--;
	}

	MotorCasaPaco::getInstance()->setShadows(values[currenPos]);
	GUI_Manager::getInstance()->changeText(textToChange, values[currenPos]);

	return true;
}

int ShadowsChangeComponent::getCurrenPos(std::string shadow)
{
	if (shadow == "No")
	{
		return 0;
	}
	else if (shadow == "Bajo")
	{
		return 1;
	}
	else if (shadow == "Medio")
	{
		return 2;
	}
	else if (shadow == "Alto")
	{
		return 3;
	}
}

void ShadowsChangeComponent::init(json& j)
{
	if (!j["button_Less"].is_null() && !j["button_More"].is_null() && !j["textToChange"].is_null())
	{
		auto helperFunction0 = std::bind(&ShadowsChangeComponent::functionMore, this, std::placeholders::_1);
		auto helperFunction1 = std::bind(&ShadowsChangeComponent::functionLess, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_Less"]), helperFunction1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_More"]), helperFunction0);

		textToChange = GUI_Manager::getInstance()->getStaticText(j["textToChange"]);
		currenPos = getCurrenPos(MotorCasaPaco::getInstance()->getShadows());

		GUI_Manager::getInstance()->changeText(textToChange, MotorCasaPaco::getInstance()->getShadows());
	}
}

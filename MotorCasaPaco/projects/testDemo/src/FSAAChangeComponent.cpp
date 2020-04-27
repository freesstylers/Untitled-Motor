#include "FSAAChangeComponent.h"
#include "MotorCasaPaco.h"

FSAAChangeComponent::FSAAChangeComponent(json& args): Component(args)
{

}

FSAAChangeComponent::~FSAAChangeComponent()
{
	Component::~Component();
}

bool FSAAChangeComponent::functionMore(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getFSAA() == "8")
	{
		currenPos = 0;
	}
	else
	{
		currenPos++;
	}

	MotorCasaPaco::getInstance()->setFSAA(values[currenPos]);
	GUI_Manager::getInstance()->changeText(textToChange, "X " + values[currenPos]);


	return true;
}

bool FSAAChangeComponent::functionLess(const CEGUI::EventArgs& e)
{
	if (MotorCasaPaco::getInstance()->getFSAA() == "0")
	{
		currenPos = 3;
	}
	else
	{
		currenPos--;
	}

	MotorCasaPaco::getInstance()->setFSAA(values[currenPos]);
	GUI_Manager::getInstance()->changeText(textToChange, "X " + values[currenPos]);

	return true;
}

int FSAAChangeComponent::getCurrenPos(std::string fsaa)
{
	if (fsaa == "0")
	{
		return 0;
	}
	else if (fsaa == "2")
	{
		return 1;
	}
	else if (fsaa == "4")
	{
		return 2;
	}
	else if (fsaa == "8")
	{
		return 3;
	}
}

void FSAAChangeComponent::init(json& j)
{
	if (!j["button_Less"].is_null() && !j["button_More"].is_null() && !j["textToChange"].is_null())
	{
		auto helperFunction0 = std::bind(&FSAAChangeComponent::functionMore, this, std::placeholders::_1);
		auto helperFunction1 = std::bind(&FSAAChangeComponent::functionLess, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_Less"]), helperFunction1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_More"]), helperFunction0);
		textToChange = GUI_Manager::getInstance()->getStaticText(j["textToChange"]);
		currenPos = getCurrenPos(MotorCasaPaco::getInstance()->getFSAA());
		GUI_Manager::getInstance()->changeText(textToChange, "X " + MotorCasaPaco::getInstance()->getFSAA());
	}
}

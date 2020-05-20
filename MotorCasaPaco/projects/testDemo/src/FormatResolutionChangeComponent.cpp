#include "FormatResolutionChangeComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

FormatResolutionChangeComponent::FormatResolutionChangeComponent(json& args): Component(args)
{
	std::vector<std::string> res43;
	std::vector<std::string> res54;
	std::vector<std::string> res1610;
	std::vector<std::string> res169;

	res43.push_back("640 x 480");
	res43.push_back("800 x 600");
	res43.push_back("832 x 624");
	res43.push_back("1024 x 768");
	res43.push_back("1152 x 872");

	res54.push_back("1280 x 1024");

	res1610.push_back("1280 x 800");
	res1610.push_back("1680 x 1050");

	res169.push_back("1280 x 720");
	res169.push_back("1600 x 900");
	res169.push_back("1920 x 1080");

	resolutions.push_back(res43);
	resolutions.push_back(res54);
	resolutions.push_back(res169);
	resolutions.push_back(res1610);
}

FormatResolutionChangeComponent::~FormatResolutionChangeComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool FormatResolutionChangeComponent::functionResLess(const CEGUI::EventArgs& e)
{
	if (currentFormat == "4 : 3")
	{
		if (currentRes == resolutions[0][0]) 
		{
			currentRes = resolutions[0][4];
			currentPos = 4;
		}
		else
		{
			currentRes = resolutions[0][currentPos - 1];
			currentPos--;
		}
	}
	else if (currentFormat == "5 : 4")
	{
		currentRes = currentRes;
	}
	else if (currentFormat == "16 : 9")
	{

		if (currentRes == resolutions[2][0])
		{
			currentRes = resolutions[2][2];
			currentPos = 2;
		}
		else
		{
			currentRes = resolutions[2][currentPos - 1];
			currentPos--;
		}
	}
	else if (currentFormat == "16 : 10")
	{
		if (currentRes == resolutions[3][0])
		{
			currentRes = resolutions[3][1];
			currentPos = 1;
		}
		else
		{
			currentRes = resolutions[3][currentPos - 1];
			currentPos--;
		}
	}

	GUI_Manager::getInstance()->changeText(ResText, currentRes);
	MotorCasaPaco::getInstance()->setResolution(currentRes);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,false);



	return true;
}

bool FormatResolutionChangeComponent::functionResMore(const CEGUI::EventArgs& e)
{
	if (currentFormat == "4 : 3")
	{
		if (currentRes == resolutions[0][4])
		{
			currentRes = resolutions[0][0];
			currentPos = 0;
		}
		else
		{
			currentRes = resolutions[0][currentPos + 1];
			currentPos++;
		}
	}
	else if (currentFormat == "5 : 4")
	{
		currentRes = currentRes;
	}
	else if (currentFormat == "16 : 9")
	{
		if (currentRes == resolutions[2][2])
		{
			currentRes = resolutions[2][0];
			currentPos = 0;
		}
		else
		{
			currentRes = resolutions[2][currentPos + 1];
			currentPos++;
		}
	}
	else if (currentFormat == "16 : 10")
	{
		if (currentRes == resolutions[3][1])
		{
			currentRes = resolutions[3][0];
			currentPos = 0;
		}
		else
		{
			currentRes = resolutions[3][currentPos + 1];
			currentPos++;
		}
	}

	GUI_Manager::getInstance()->changeText(ResText, currentRes);
	MotorCasaPaco::getInstance()->setResolution(currentRes);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,false);

	return true;
}

bool FormatResolutionChangeComponent::functionForLess(const CEGUI::EventArgs& e)
{
	if (currentFormat == "4 : 3")
	{
		currentFormat = "16 : 10";
		currentRes = resolutions[3][0];
		currentPos = 0;
	}
	else if (currentFormat == "5 : 4")
	{
		currentFormat = "4 : 3";
		currentRes = resolutions[0][0];
		currentPos = 0;
	}
	else if (currentFormat == "16 : 9")
	{
		currentFormat = "5 : 4";
		currentRes = resolutions[1][0];
		currentPos = 0;
	}
	else if (currentFormat == "16 : 10")
	{
		currentFormat = "16 : 9";
		currentRes = resolutions[2][0];
		currentPos = 0;
	}

	GUI_Manager::getInstance()->changeText(ForText, currentFormat);
	GUI_Manager::getInstance()->changeText(ResText, currentRes);
	MotorCasaPaco::getInstance()->setScreenProportion(currentFormat);
	MotorCasaPaco::getInstance()->setResolution(currentRes);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,false);

	return true;
}

bool FormatResolutionChangeComponent::functionForMore(const CEGUI::EventArgs& e)
{
	if (currentFormat == "4 : 3")
	{
		currentFormat = "5 : 4";
		currentRes = resolutions[1][0];
		currentPos = 0;
	}
	else if (currentFormat == "5 : 4")
	{
		currentFormat = "16 : 9";
		currentRes = resolutions[2][0];
		currentPos = 0;
	}
	else if (currentFormat == "16 : 9")
	{
		currentFormat = "16 : 10";
		currentRes = resolutions[3][0];
		currentPos = 0;
	}
	else if (currentFormat == "16 : 10")
	{
		currentFormat = "4 : 3";
		currentRes = resolutions[0][0];
		currentPos = 0;
	}

	GUI_Manager::getInstance()->changeText(ForText, currentFormat);
	GUI_Manager::getInstance()->changeText(ResText, currentRes);
	MotorCasaPaco::getInstance()->setScreenProportion(currentFormat);
	MotorCasaPaco::getInstance()->setResolution(currentRes);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,false);

	return true;
}

bool FormatResolutionChangeComponent::ReceiveEvent(Event& event)
{
	if (event.type == "RESET_GRAPHIC_INFO") {
		currentFormat = MotorCasaPaco::getInstance()->getScreenProportion();
		currentRes = MotorCasaPaco::getInstance()->getResolution();
		currentPos = getCurrentPos(currentFormat, currentRes);
		GUI_Manager::getInstance()->changeText(ResText, currentRes);
		GUI_Manager::getInstance()->changeText(ForText, currentFormat);
	}
	return false;
}

int FormatResolutionChangeComponent::getCurrentPos(std::string currentFormat_, std::string currentRes_)
{

	if (currentFormat_ == "4 : 3")
	{
		if (currentRes_ == "640 x 480")
		{
			return 0;
		}
		else if (currentRes_ == "800 x 600")
		{
			return 1;
		}
		else if (currentRes_ == "832 x 624")
		{
			return 2;
		}
		else if (currentRes_ == "1024 x 768")
		{
			return 3;
		}
		else if (currentRes_ == "1152 x 872")
		{
			return 4;
		}
	}
	else if (currentFormat_ == "5 : 4")
	{
		return 0;
	}
	else if (currentFormat_ == "16 : 9")
	{
		if (currentRes_ == "1280 x 720")
		{
			return 0;
		}
		else if (currentRes_ == "1600 x 900")
		{
			return 1;
		}
		else if (currentRes_ == "1920 x 1080")
		{
			return 2;
		}
	}
	else if (currentFormat_ == "16 : 10")
	{
		if (currentRes_ == "1280 x 800")
		{
			return 0;
		}
		else if (currentRes_ == "1650 x 1050")
		{
			return 1;
		}
	}
}

void FormatResolutionChangeComponent::init(json& j)
{
	if (!j["button_Res_Less"].is_null() && !j["button_Res_More"].is_null() && !j["ResText"].is_null() && !j["button_For_Less"].is_null() && !j["button_For_More"].is_null() && !j["ForText"].is_null())
	{
		auto helperFunction0 = std::bind(&FormatResolutionChangeComponent::functionResMore, this, std::placeholders::_1);
		auto helperFunction1 = std::bind(&FormatResolutionChangeComponent::functionResLess, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_Res_Less"]), helperFunction1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_Res_More"]), helperFunction0);
		ResText = GUI_Manager::getInstance()->getStaticText(j["ResText"]);

		auto helperFunction2 = std::bind(&FormatResolutionChangeComponent::functionForMore, this, std::placeholders::_1);
		auto helperFunction3 = std::bind(&FormatResolutionChangeComponent::functionForLess, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_For_Less"]), helperFunction3);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button_For_More"]), helperFunction2);
		ForText = GUI_Manager::getInstance()->getStaticText(j["ForText"]);
		
		currentFormat = MotorCasaPaco::getInstance()->getScreenProportion();
		currentRes = MotorCasaPaco::getInstance()->getResolution();
		currentPos = getCurrentPos(currentFormat, currentRes);
		GUI_Manager::getInstance()->changeText(ResText, currentRes);
		GUI_Manager::getInstance()->changeText(ForText, currentFormat);

		EventManager::getInstance()->RegisterListener(this, "RESET_GRAPHIC_INFO");
	}
}

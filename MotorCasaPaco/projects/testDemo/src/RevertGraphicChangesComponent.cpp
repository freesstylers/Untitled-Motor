#include "RevertGraphicChangesComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

RevertGraphicChangesComponent::RevertGraphicChangesComponent(json& args): Component(args)
{

}

RevertGraphicChangesComponent::~RevertGraphicChangesComponent()
{
	Component::~Component();
}

bool RevertGraphicChangesComponent::function(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->revertGraphicChanges();
	AudioManager::getInstance()->playSound("assets/sound/buttonSound.mp3", 0);

	Event evt = Event("RESET_GRAPHIC_INFO");
	EventManager::getInstance()->EmitEvent(evt);

	return true;
}

void RevertGraphicChangesComponent::init(json& j)
{
	if (!j["button"].is_null() && !j["fullscreen"].is_null() && !j["resolution"].is_null() && !j["screenProportion"].is_null() && !j["vsync"].is_null())
	{
		auto helperFunction0 = std::bind(&RevertGraphicChangesComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button"]), helperFunction0);

		fullscreen = GUI_Manager::getInstance()->getStaticText(j["fullscreen"]);
		resolution = GUI_Manager::getInstance()->getStaticText(j["resolution"]);
		screenProportion = GUI_Manager::getInstance()->getStaticText(j["screenProportion"]);
		vsync = GUI_Manager::getInstance()->getStaticText(j["vsync"]);
	}
}

#include "RevertAdvancedGraphicChangesComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

RevertAdvancedGraphicChangesComponent::RevertAdvancedGraphicChangesComponent(json& args) : Component(args)
{

}

RevertAdvancedGraphicChangesComponent::~RevertAdvancedGraphicChangesComponent()
{
	Component::~Component();
}

bool RevertAdvancedGraphicChangesComponent::function(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->revertAdvancedGraphicChanges();

	Event evt = Event("RESET_GRAPHIC_INFO");
	EventManager::getInstance()->EmitEvent(evt);
	
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,false);

	return true;
}

void RevertAdvancedGraphicChangesComponent::init(json& j)
{
	if (!j["button"].is_null() && !j["fsaa"].is_null() && !j["gamma"].is_null() && !j["shadows"].is_null())
	{
		auto helperFunction0 = std::bind(&RevertAdvancedGraphicChangesComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button"]), helperFunction0);

		fsaa = GUI_Manager::getInstance()->getStaticText(j["fsaa"]);
		gamma = GUI_Manager::getInstance()->getStaticText(j["gamma"]);
		shadows = GUI_Manager::getInstance()->getStaticText(j["shadows"]);
	}
}
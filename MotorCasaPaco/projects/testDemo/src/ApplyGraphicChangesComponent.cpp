#include "ApplyGraphicChangesComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

ApplyGraphicChangesComponent::ApplyGraphicChangesComponent(json& args): Component(args)
{

}

ApplyGraphicChangesComponent::~ApplyGraphicChangesComponent()
{
	Component::~Component();
}

bool ApplyGraphicChangesComponent::function(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeGraphicComponents();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0,true);
	return true;
}

void ApplyGraphicChangesComponent::init(json& j)
{
	if (!j["button"].is_null())
	{
		auto helperFunction0 = std::bind(&ApplyGraphicChangesComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button"]), helperFunction0);
	}
}

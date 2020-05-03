#include "ApplyAdvancedGraphicChangesComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"

ApplyAdvancedGraphicChangesComponent::ApplyAdvancedGraphicChangesComponent(json& args): Component(args)
{
}

ApplyAdvancedGraphicChangesComponent::~ApplyAdvancedGraphicChangesComponent()
{
	Component::~Component();
}

bool ApplyAdvancedGraphicChangesComponent::function(const CEGUI::EventArgs& e)
{
	MotorCasaPaco::getInstance()->changeAdvancedGraphicComponents();
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 0);
	return true;
}

void ApplyAdvancedGraphicChangesComponent::init(json& j)
{
	if (!j["button"].is_null())
	{
		auto helperFunction0 = std::bind(&ApplyAdvancedGraphicChangesComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["button"]), helperFunction0);
	}
}

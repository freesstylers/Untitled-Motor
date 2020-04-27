#include "ApplyGraphicChangesComponent.h"
#include "MotorCasaPaco.h"

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

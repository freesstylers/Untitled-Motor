#include "ChangeGraphicSceneComponent.h"
#include "MotorCasaPaco.h"

class Ogre::Root;
class Ogre::SceneManager;

ChangeGraphicSceneComponent::ChangeGraphicSceneComponent(json& args) : Component(args)
{
}

ChangeGraphicSceneComponent::~ChangeGraphicSceneComponent()
{
	Component::~Component();
}

bool ChangeGraphicSceneComponent::function(const CEGUI::EventArgs& e)
{
	if (advanced)
		MotorCasaPaco::getInstance()->revertAdvancedGraphicChanges();
	else
		MotorCasaPaco::getInstance()->revertGraphicChanges();

	MotorCasaPaco::getInstance()->changeScene(sceneToLoad);
	return true;
}

void ChangeGraphicSceneComponent::init(json& j)
{
	if (!j["buttonName"].is_null() && !j["sceneName"].is_null() && !j["advanced"].is_null())
	{
		std::string interm = j["sceneName"];
		sceneToLoad = interm;
		auto helperFunction = std::bind(&ChangeGraphicSceneComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["buttonName"]), helperFunction);

		if (j["advanced"] == "Si")
			advanced = true;
		else if (j["advanced"] == "No")
			advanced = false;
	}
}
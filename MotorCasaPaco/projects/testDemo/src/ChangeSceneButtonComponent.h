#pragma once
#ifndef CHANGESCENECOMPONENT_H
#define CHANGESCENECOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ChangeSceneButtonComponent: public Component
{

public:
	ChangeSceneButtonComponent(json& args);
	~ChangeSceneButtonComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
private:
	std::string sceneToLoad;
};

#endif

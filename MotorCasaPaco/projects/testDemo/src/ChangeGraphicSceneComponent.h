#pragma once
#ifndef CHANGEGRAPHICSCENECOMPONENT_H
#define CHANGEGRAPHICSCENECOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ChangeGraphicSceneComponent : public Component
{

public:
	ChangeGraphicSceneComponent(json& args);
	~ChangeGraphicSceneComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
private:
	std::string sceneToLoad;
	bool advanced;
};

#endif

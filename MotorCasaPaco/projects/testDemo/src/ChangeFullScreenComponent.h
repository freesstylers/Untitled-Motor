#pragma once
#ifndef CHANGEFULLSCREENCOMPONENT_H
#define CHANGEFULLSCREENCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ChangeFullScreenComponent : public Component
{

public:
	ChangeFullScreenComponent(json& args);
	~ChangeFullScreenComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
private:
	CEGUI::Window* textToChange;
};

#endif


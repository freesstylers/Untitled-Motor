#pragma once
#ifndef CHANGEGAMMACOMPONENT_H
#define CHANGEGAMMACOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ChangeGammaComponent : public Component
{

public:
	ChangeGammaComponent(json& args);
	~ChangeGammaComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;

private:
	CEGUI::Window* textToChange;
};

#endif


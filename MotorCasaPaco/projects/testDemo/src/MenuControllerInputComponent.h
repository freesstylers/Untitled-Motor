#pragma once
#ifndef MENUCONTROLLERINPUTCOMPONENT_H
#define MENUCONTROLLERINPUTCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class MenuControllerInputComponent : public Component
{

public:
	MenuControllerInputComponent(json& args);
	~MenuControllerInputComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;
	void update();
private:
	int posX = 0;
	int posY = 0;

	std::vector<float> positionsX;
	std::vector<float> positionsY;
	int tam;
	int currenPos;
};

#endif


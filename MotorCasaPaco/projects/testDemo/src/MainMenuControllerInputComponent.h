#pragma once
#ifndef MAINMENUCONTROLLERINPUTCOMPONENT_H
#define MAINMENUCONTROLLERINPUTCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class MainMenuControllerInputComponent : public Component
{

public:
	MainMenuControllerInputComponent(json& args);
	~MainMenuControllerInputComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;
	void update();
private:
	
	std::vector<float> positionsX;
	std::vector<float> positionsY;
	int tam;
	int currenPos;
	float delay;
	float currentTime;
};

#endif


#pragma once
#ifndef MAINMENUINPUTCOMPONENT_H
#define MAINMENUINPUTCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class MainMenuInputComponent : public Component
{

public:
	MainMenuInputComponent(json& args);
	~MainMenuInputComponent();
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


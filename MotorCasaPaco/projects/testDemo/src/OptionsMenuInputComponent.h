#pragma once
#ifndef OPTIONSMENUINPUTCOMPONENT_H
#define OPTIONSMENUINPUTCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class OptionsMenuInputComponent : public Component
{

public:
	OptionsMenuInputComponent(json& args);
	~OptionsMenuInputComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;
	void update();
private:
	std::vector<float> positionsXTopButtons;
	std::vector<float> positionsYTopButtons;
	std::vector<float> positionsXDownButtons;
	int yDownButtons;

	float xExtra;
	float yExtra;

	int tamDownButtons = 0;
	int tamTopButtons = 0;

	int currentXTopButtons = 0;
	int currentYTopButtons = 0;
	int currentPosDownButtons = 2;

	float delay;
	float currentTime;

	int where = 0;
};

#endif


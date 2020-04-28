#pragma once
#ifndef FSAACHANGECOMPONENT_H
#define FSAACHANGECOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class FSAAChangeComponent : public Component
{

public:
	FSAAChangeComponent(json& args);
	~FSAAChangeComponent();
	void init(json& j) override;
	bool functionMore(const CEGUI::EventArgs& e);
	bool functionLess(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;

private:
	int getCurrenPos(std::string fsaa);
	CEGUI::Window* textToChange;
	std::string values[4] = { "0" , "2", "4", "8"};
	int currenPos;
};

#endif


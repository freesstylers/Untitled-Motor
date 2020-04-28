#pragma once
#ifndef SHADOWSCHANGECOMPONENT_H
#define SHADOWSCHANGECOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ShadowsChangeComponent : public Component
{

public:
	ShadowsChangeComponent(json& args);
	~ShadowsChangeComponent();
	void init(json& j) override;
	bool functionMore(const CEGUI::EventArgs& e);
	bool functionLess(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;

private:
	int getCurrenPos(std::string fsaa);
	CEGUI::Window* textToChange;
	std::string values[4] = { "No" , "Bajo", "Medio", "Alto"};
	int currenPos;
};

#endif


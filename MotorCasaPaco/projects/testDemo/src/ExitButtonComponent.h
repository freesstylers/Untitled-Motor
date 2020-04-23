#pragma once
#ifndef EXITBUTTONCOMPONENT_H
#define EXITBUTTONCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ExitButtonComponent : public Component
{

public:
	ExitButtonComponent(json& args);
	~ExitButtonComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
};

#endif


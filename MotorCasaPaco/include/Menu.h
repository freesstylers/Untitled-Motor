#pragma once
#include "MotorCasaPaco.h"
#include "GUI/GUI_Manager.h"

class Menu
{
public:
	Menu(GUI_Manager* mgr);
	bool test(const CEGUI::EventArgs& e);
	void setEvent(int code, CEGUI::PushButton* button);

	GUI_Manager* manager;
};


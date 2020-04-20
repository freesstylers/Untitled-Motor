#include "Menu.h"

Menu::Menu(GUI_Manager* mgr)
{
	manager = mgr;
}

bool Menu::test(const CEGUI::EventArgs& e) {
	std::cout << testString_;
	return true;
}

void Menu::setEvent(int code, CEGUI::PushButton* b)
{
	switch (code)
	{
	default:
		auto helperFunction = std::bind(&Menu::test, this, std::placeholders::_1);
		manager->getInstance()->setEvents(b, helperFunction);
		break;
	}
}

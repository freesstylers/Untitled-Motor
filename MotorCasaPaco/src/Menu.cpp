#include "Menu.h"

Menu::Menu(GUI_Manager* mgr)
{
	manager = mgr;
}

bool Menu::test(const CEGUI::EventArgs& e) {
	std::cout << "joder";
	return true;
}

void Menu::setEvent(int code, CEGUI::PushButton* b)
{
	switch (code)
	{
	default:
		manager->getInstance()->setEvents(b, &Menu::test, this);
		break;
	}
}

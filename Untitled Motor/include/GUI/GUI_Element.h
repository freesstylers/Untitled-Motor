#pragma once
#include "CEGUI/CEGUI.h"
#include "Entity/Transform.h"


class GUI_Element
{
public:
	GUI_Element(CEGUI::Window* window);
	//GUI_Element(json& args);

	~GUI_Element();

	CEGUI::Window* getWindowElement();

	void setPosition(int x, int y);
	int getPosX();
	int getPosY();

	void setSize(int x, int y);
	void setPriority(int value);
	//int getWidth();
	//int getHeight();
	int getPriority();

	GUI_Element getChild(std::string name);
	GUI_Element getChildIndex(int index);
	GUI_Element addChild(const std::string& type, const std::string& name);

	void scale(double value);

	void setText(std::string text);
	
	void setAlpha(int value);
	int getAlpha();

	bool isActive();
	void setActive(bool value);

protected:

	Transform* transform;
	CEGUI::Window* elementWindow;
};


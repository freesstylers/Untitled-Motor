#pragma once
#include "Entity/Transform.h" //Dejado para mantener Ogre para el vector 2, si eso

namespace CEGUI {
	class Window;
//	class UVector2;
}

class GUI_Element
{
public:
	GUI_Element(CEGUI::Window* window);

	~GUI_Element();

	CEGUI::Window* getWindowElement();

	void setPosition(int x, int y);
	//CEGUI::UVector2 getPos();
	int getPosX();
	int getPosY();

	void setSize(int x, int y);

	GUI_Element getChild(std::string name);
	GUI_Element getChildIndex(int index);
	//GUI_Element addChild(CEGUI::Window* window, const std::string& name);
	void addChild(CEGUI::Window* window);

	void scale(double value);

	void setText(std::string text);
	
	void setAlpha(int value);
	int getAlpha();

	bool isActive();
	void setActive(bool value);

protected:

	//Transform* transform;
	CEGUI::Window* elementWindow;
};


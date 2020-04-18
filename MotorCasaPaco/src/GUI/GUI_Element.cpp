#include "GUI/GUI_Element.h"
#include "CEGUI/CEGUI.h"
#include "checkML.h"

GUI_Element::GUI_Element(CEGUI::Window* window)
{
	elementWindow = window;
}

GUI_Element::~GUI_Element()
{
	//delete elementWindow;
}

CEGUI::Window* GUI_Element::getWindowElement()
{
	return elementWindow;
}

void GUI_Element::setPosition(int x, int y)
{
	elementWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(x, 0.0f), CEGUI::UDim(y, 0.0f)));
}

int GUI_Element::getPosX()
{
	CEGUI::UVector2 v2 = elementWindow->getPosition();
	return (v2.d_x.d_offset);
}

int GUI_Element::getPosY()
{
	CEGUI::UVector2 v2 = elementWindow->getPosition();
	return (v2.d_y.d_offset);
}

/*Ogre::Vector2 GUI_Element::getPos()
{
	Ogre::Vector2 v;
	CEGUI::UVector2 v2 = elementWindow->getPosition();
	v = Ogre::Vector2(v2.d_x.d_offset, v2.d_y.d_offset);

	return v;
}*/

void GUI_Element::setSize(int x, int y)
{
	elementWindow->setSize(CEGUI::USize(CEGUI::UDim(x, 0), CEGUI::UDim(y, 0)));
}

GUI_Element GUI_Element::getChild(std::string name)
{
	return elementWindow->getChild(name);
}

GUI_Element GUI_Element::getChildIndex(int index)
{
	return elementWindow->getChildAtIdx(index);
}

void GUI_Element::addChild(CEGUI::Window* window)
{
	elementWindow->addChild(window);
}

/*GUI_Element GUI_Element::addChild(const std::string& type, const std::string& name)
{
	elementWindow->addChild(CEGUI::WindowManager::getSingleton().createWindow(type, name));
	return getChild(name);
}*/

void GUI_Element::scale(double value)
{
}

void GUI_Element::setText(std::string text)
{
	elementWindow->setText(text);
}

void GUI_Element::setAlpha(int value)
{
	elementWindow->setAlpha(value);
}

int GUI_Element::getAlpha()
{
	return elementWindow->getAlpha();
}

bool GUI_Element::isActive()
{
	return elementWindow->isVisible();
}

void GUI_Element::setActive(bool value)
{
	elementWindow->setVisible(value);
}

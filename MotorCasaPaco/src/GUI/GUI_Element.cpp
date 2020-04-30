#include "GUI/GUI_Element.h"
#include "CEGUI/CEGUI.h"
#include "checkML.h"

GUI_Element::GUI_Element(CEGUI::Window* window)
{
	elementWindow = window;
}

GUI_Element::~GUI_Element()
{
}

CEGUI::Window* GUI_Element::getWindowElement()
{
	return elementWindow;
}

void GUI_Element::setPosition(int x, int y)
{
	elementWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0, x), CEGUI::UDim(0, y)));
}

/*CEGUI::UVector2 GUI_Element::getPos()
{
	CEGUI::UVector2 v2 = elementWindow->getPosition();

	return v2;
}*/

float GUI_Element::getPosXScale()
{
	CEGUI::UVector2 v2 = elementWindow->getPosition();
	return (v2.d_x.d_scale);
}

float GUI_Element::getPosYScale()
{

	CEGUI::UVector2 v2 = elementWindow->getPosition();
	return (v2.d_y.d_scale);
}

float GUI_Element::getPosXAbsolute()
{
	return elementWindow->getOuterRectClipper().d_min.d_x;
}

float GUI_Element::getPosYAbsolute()
{
	return elementWindow->getOuterRectClipper().d_min.d_y;
}

float GUI_Element::getCenterPointXAbsolute()
{
	float i = elementWindow->getOuterRectClipper().d_min.d_x;
	float j = elementWindow->getOuterRectClipper().d_max.d_x;

	float k = (i + j) / 2;

	return k;
}

float GUI_Element::getCenterPointYAbsolute()
{
	float i = elementWindow->getOuterRectClipper().d_min.d_y;
	float j = elementWindow->getOuterRectClipper().d_max.d_y;

	float k = (i + j) / 2;

	return k;
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

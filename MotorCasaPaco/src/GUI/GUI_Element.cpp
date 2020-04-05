#include "GUI/GUI_Element.h"

GUI_Element::GUI_Element(CEGUI::Window* window)
{
	elementWindow = window;
}

/*GUI_Element::GUI_Element(json& args)//: Component(args)
{
}*/

GUI_Element::~GUI_Element()
{
	delete elementWindow;
	delete transform;
}

CEGUI::Window* GUI_Element::getWindowElement()
{
	return elementWindow;
}

void GUI_Element::setPosition(int x, int y)
{
	transform->setPosition(Ogre::Vector3(x, y, 0));
}

int GUI_Element::getPosX()
{
	return transform->getPosition().x;
}

int GUI_Element::getPosY()
{
	return transform->getPosition().y;
}

void GUI_Element::setSize(int x, int y)
{
	elementWindow->setSize(CEGUI::USize(CEGUI::UDim(0, x), CEGUI::UDim(0, y)));
}

void GUI_Element::setPriority(int value)
{
	Ogre::Vector3 v = transform->getPosition();

	transform->setPosition(Ogre::Vector3(v.x, v.y, value));
}

/*int GUI_Element::getWidth()
{
	return elementWindow->getSize().one_width;
}

int GUI_Element::getHeight()
{
	return elementWindow->getSize().one_height;
}*/

int GUI_Element::getPriority()
{
	return transform->getPosition().z;
}

GUI_Element GUI_Element::getChild(std::string name)
{
	return elementWindow->getChild(name);
}

GUI_Element GUI_Element::getChildIndex(int index)
{
	return elementWindow->getChildAtIdx(index);
}

GUI_Element GUI_Element::addChild(const std::string& type, const std::string& name)
{
	elementWindow->addChild(CEGUI::WindowManager::getSingleton().createWindow(type, name));
	return getChild(name);
}

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

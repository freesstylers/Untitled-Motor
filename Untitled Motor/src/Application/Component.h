#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "EventListener.h"
#include "EventManager.h"

class Entity;

//Puede/debe heredar de el listener para los mensajes
class Component: public EventListener
{
public:
	Component(std::string tag);
	virtual ~Component();

	void setEntity(Entity* e);
	Entity* getEntity();
	std::string const getTag();

	virtual void init();
	virtual void update();
	virtual void render();

	bool ReceiveEvent(Event& event) override { return true; };

private:
	std::string tag_;
	Entity* e_;
};

#endif // !COMPONENT_H
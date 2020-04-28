#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include "Events/EventManager.h"
#include "Others/General.h"

class Entity;

//Puede/debe heredar de el listener para los mensajes
class Component: public EventListener
{
public:
	Component(json& args);
	virtual ~Component();

	void setEntity(Entity* e);
	Entity* getEntity();
	std::string const getTag();

	virtual void init(json& args);
	virtual void redefine(json& args);
	virtual void start();
	virtual void preupdate();
	virtual void physicsUpdate();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();

	void setActive(bool active);
	void setActiveOnHierarchy(bool active);

	const bool isActive();
	const bool isActiveOnHierarchy();

	virtual void onSetParent(Entity* parent);
	virtual void onActivated();
	virtual void onDeactivated();

	virtual bool ReceiveEvent(Event& event) override { return false; };

protected:
	std::string tag_;
	Entity* e_;

private:
	bool active_ = true, activeOnHierarchy_ = true;
};

#endif // !COMPONENT_H
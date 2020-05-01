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

	virtual void OnCollision(Entity* other);

	/* DO NOT CALL MANUALLY, use 'setEnabled()' instead */
	void setActiveOnHierarchy(bool active);
	void setEnabled(bool enabled);

	const bool isActive();
	const bool isEnabled();
	const bool isActiveOnHierarchy();

	virtual void onSetParent(Entity* parent);
	virtual void onActivated();
	virtual void onDeactivated();

	virtual bool ReceiveEvent(Event& event) override { return false; };

protected:
	std::string tag_;
	Entity* e_;

private:
	bool enabled_ = true, activeOnHierarchy_ = true;
	bool startWasCalled_ = false;
};

#endif // !COMPONENT_H
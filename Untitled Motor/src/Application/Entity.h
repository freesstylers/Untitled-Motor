#pragma once
#include "Component.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	virtual void update();
	void addComponent(Component* component);
protected:

private:
	std::vector<Component> components;
};

#endif
#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <json.hpp>

using json = nlohmann::json;

class Entity;

//Puede/debe heredar de el listener para los mensajes
class Component
{
public:
	Component(json& args);
	virtual ~Component();

	void setEntity(Entity* e);
	std::string const getTag();

	virtual void init();
	virtual void initFromJson(json& j);
	virtual void update();
	virtual void render();

private:
	std::string tag_;
	Entity* e_;
};

#endif // !COMPONENT_H
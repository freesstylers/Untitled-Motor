#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <json.hpp>

using json = nlohmann::json;

class Component;

using uptr_cmp = std::unique_ptr<Component>;


class Entity {
public:
	Entity(std::string name);
	void update();

	template <typename T>
	T* getComponent(std::string tag);

	template <typename T>
	T* addComponent(json args);

	bool hasComponent(std::string tag);

	template<typename T>
	void toggleComponent(std::string tag, bool state);

	void setName(std::string name);
	std::string const getName();

	void setActive(bool state);
	bool const getActive();
protected:

private:
	bool isActive_;
	std::string name_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;
};

#endif
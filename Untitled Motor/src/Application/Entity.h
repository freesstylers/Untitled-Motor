#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <json.hpp>
#include "Component.h"

using json = nlohmann::json;

class Scene;

using uptr_cmp = std::unique_ptr<Component>;


class Entity {
public:
	Entity(Scene* scene, const std::string& name);
	void update();

	template <typename T>
	T* getComponent(const std::string& tag);

	template <typename T>
	T* addComponent(json& args);

	void addComponentFromJson(json& args);

	bool hasComponent(const std::string& tag);

	template<typename T>
	void toggleComponent(const std::string& tag, bool state);

	void setName(const std::string& name);
	std::string const getName();

	void setActive(bool state);
	bool const getActive();

	void init(json& args);
protected:

private:
	bool isActive_;
	std::string name_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;

	Scene* scene;
};

#endif
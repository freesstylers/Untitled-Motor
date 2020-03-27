#pragma once
#include "Component.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <json.hpp>
#include "Component.h"
#include "Factory.h"

using json = nlohmann::json;

class Scene;

#include "EventListener.h"
#include "EventManager.h"

using uptr_cmp = std::unique_ptr<Component>;

class Entity: public EventListener {
public:
	Entity(Scene* scene, const std::string& name);
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();

	template <typename T>
	T* getComponent(const std::string& tag) {
		if (!hasComponent(tag))
			return nullptr;
		return static_cast<T*>(map_[tag]);
	};

	template <typename T>
	T* addComponent(json& args) {
		T* c(Factory::template createComponent<T>(args));
		components_.push_back(uptr_cmp(c));
		map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
		c->setEntity(this);
		c->init(args);
		return c;
	};

	void addComponentFromJson(json& args);

	bool hasComponent(const std::string& tag);

	template<typename T>
	void toggleComponent(const std::string& tag, bool state) {
		getComponent<T>(tag).toggle(state);
	};

	void setName(const std::string& name);
	std::string const getName();

	void setActive(bool state);
	bool const getActive();

	Scene* getScene();

	Entity* getParent();
	std::map<std::string, Entity*> getChildren();
	Entity* getChild(std::string name);

	bool setParent(std::string name);
	void clearParent();

	void init(json& args);
	
	bool ReceiveEvent(Event& event) override;

protected:

private:
	bool isActive_;
	std::string name_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;

	Entity* parent_;
	std::map<std::string, Entity*> children_;

	Scene* scene_;
};

#endif
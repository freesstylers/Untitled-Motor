#pragma once
#include "Component.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "EventListener.h"
#include "EventManager.h"

class Component;

using uptr_cmp = std::unique_ptr<Component>;

class Entity: public EventListener {
public:
	Entity(std::string name);
	void update();

	template <typename T>
	T* getComponent(std::string tag) {
		return static_cast<T*>(map_.find(tag));
	}

	template <typename T, typename ... Targs>
	T* addComponent(Targs&& ... mArgs) {
		T* c(new T(std::forward<Targs>(mArgs)...)); //Alomejor hay que usar factory
		components_.push_back(uptr_cmp(c));
		map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
		c->setEntity(this); //Uso para conseguir otros componentes
		c->init();
		return c;
	}

	bool hasComponent(std::string tag);

	template<typename T>
	void toggleComponent(std::string tag, bool state);

	void setName(std::string name);
	std::string const getName();

	void setActive(bool state);
	bool const getActive();

	bool ReceiveEvent(Event& event) override;

protected:

private:
	bool isActive_;
	std::string name_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;
};

#endif
#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>
#include <string>
#include <memory>

class Component;

using namespace std;
using uptr_cmp = unique_ptr<Component>;


class Entity {
public:
	Entity(string name);
	void update();

	template <typename T>
	T* getComponent(string tag);

	template <typename T, typename ... Targs>
	T* addComponent(string tag, Targs&& ... mArgs);

	bool hasComponent(string tag);

	template<typename T>
	void toggleComponent(string tag, bool state);

	void setName(string name);
	string const getName();

	void setActive(bool state);
	bool const getActive();
protected:

private:

	bool isActive_;
	string name_;
	vector<uptr_cmp> components_; 
	map<string, Component*> map_;

};

#endif
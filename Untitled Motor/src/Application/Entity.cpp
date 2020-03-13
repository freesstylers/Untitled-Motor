#include "Entity.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <utility>
#include "Component.h"

Entity::Entity(string name): name_(name) {
	
}

void Entity::update()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		components_[i]->update();
	}
}

template<typename T>
T* Entity::getComponent(std::string tag)
{
	return static_cast<T*>(map_.find(tag));
}

template<typename T, typename ... Targs>
T* Entity::addComponent(string tag, Targs&& ... mArgs){
	T* c(new T(forward<Targs>(mArgs)...)); //Alomejor hay que usar factory
	uptr_cmp uPtr(c);
	components_.push_back(uPtr);
	map_.insert(pair<string, Component*>(tag, c));
	c->setEntity(this); //Uso para conseguir otros componentes
	c->init();
	return c;
}

bool Entity::hasComponent(string tag) {
	return &map_.find(tag) != nullptr;
}

template<typename T>
void Entity::toggleComponent(string tag, bool state) {
	getComponent(tag).toggle(state);
}

void Entity::setName(string name) {
	name_ = name;
}

string const Entity::getName() {
	return name_;
}

void Entity::setActive(bool state) {
	isActive_ = state;
}

bool const Entity::getActive() {
	return isActive_;
}
#include "Entity.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <utility>
#include "Component.h"

using namespace std;

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

bool Entity::hasComponent(string tag) {
	return &map_.find(tag) != nullptr;
}

template<typename T>
T* Entity::getComponent(std::string tag)
{
	return static_cast<T*>(map_.find(tag));
}

template<typename T>
T* Entity::addComponent(json args)
{
	T* c(/*call factory*/);
	components_.push_back(uptr_cmp(c));
	map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
	c->setEntity(this);
	c->init();
	return c;
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
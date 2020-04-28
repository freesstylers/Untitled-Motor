#include "Entity/Component.h"

#include "Entity/Entity.h"
#include "checkML.h"

using namespace std;

Component::Component(json& args) {
	std::string str = args["type"];
	tag_ = str;
}

Component::~Component() {
	//e_ = nullptr;
}

void Component::setEntity(Entity* e) { e_ = e; }

Entity* Component::getEntity(){ return e_; }

string const Component::getTag() {
	return tag_;
}

//Se rellenan segun convenga en sus hijos

void Component::init(json& args) { }

void Component::redefine(json& args) {	}

void Component::start() { }

void Component::preupdate() { }

void Component::physicsUpdate() { }

void Component::update() { }

void Component::lateUpdate() { }

void Component::render() { }

void Component::setActive(bool active) {
	active_ = active;

	if (activeOnHierarchy_) {
		if (activeOnHierarchy_ && active_) onActivated();
		else if (!activeOnHierarchy_) onDeactivated();
	}
}

void Component::setActiveOnHierarchy(bool active) {
	activeOnHierarchy_ = active;

	if (active_) {
		if (activeOnHierarchy_ && active_) onActivated();
		else if (!activeOnHierarchy_) onDeactivated();
	}
}

const bool Component::isActive()
{
	return active_;
}

const bool Component::isActiveOnHierarchy()
{
	return activeOnHierarchy_;
}

void Component::onSetParent(Entity* parent) { }

void Component::onActivated() { }

void Component::onDeactivated() { }

#include "Entity/Component.h"

#include "Entity/Entity.h"
#include "checkML.h"

using namespace std;

Component::Component(json& args) {
	std::string str = args["type"];
	tag_ = str;

	if (!args["enabled"].is_null() && args["enabled"] == "false")
		enabled_ = false;
}

Component::Component(std::string tag) {
	tag_ = tag;
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

void Component::OnCollision(Entity* other){ }

void Component::setEnabled(bool enabled) {
	if (startWasCalled_ && enabled == enabled_)
		return;

	enabled_ = enabled;

	if (activeOnHierarchy_) {
		if (enabled_) {
			if (!startWasCalled_) {
				start();
				startWasCalled_ = true;
			}
			onActivated();
		}
		else if (startWasCalled_) onDeactivated();
	}
}

void Component::setActiveOnHierarchy(bool active) {
	if (startWasCalled_ && active == activeOnHierarchy_)
		return;

	activeOnHierarchy_ = active;

	if (enabled_) {
		if (activeOnHierarchy_) {
			if (!startWasCalled_) {
				start();
				startWasCalled_ = true;
			}
			onActivated();
		}
		else if (startWasCalled_) onDeactivated();
	}
}

const bool Component::isActive() {
	return enabled_ && activeOnHierarchy_;
}

const bool Component::isEnabled() {
	return enabled_;
}

const bool Component::isActiveOnHierarchy() {
	return activeOnHierarchy_;
}

void Component::onSetParent(Entity* parent) { }

void Component::onActivated() { }

void Component::onDeactivated() { }

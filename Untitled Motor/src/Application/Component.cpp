#include "Component.h"

#include "Entity.h"

using namespace std;

Component::Component(json& args) {
	std::string str = args["tag"];
	tag_ = str;
}

Component::~Component() {
	e_ = nullptr;
}

void Component::setEntity(Entity* e) { e_ = e; }

Entity* Component::getEntity(){ return e_; }

string const Component::getTag() {
	return tag_;
}

//Se rellenan segun convenga en sus hijos

void Component::init() { }

void Component::initFromJson(json& j)	{ }

void Component::preupdate() { }

void Component::update() { }

void Component::render() { }

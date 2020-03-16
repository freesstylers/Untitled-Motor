#include "Component.h"

using namespace std;

Component::Component(string tag): tag_(tag) {

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

void Component::preupdate() { }

void Component::update() { }

void Component::render() { }

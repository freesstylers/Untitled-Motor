#include "Entity/Entity.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <utility>
#include "Scene/Scene.h"
#include "Scene/JsonFactoryParser.h"
#include "Entity/Transform.h"
#include "checkML.h"

using namespace std;

Entity::Entity(Scene* scene, const std::string& name, const std::string& tag, const bool enabled): scene_(scene), 
	name_(name), tag_(tag), enabled_(enabled)
{
	
}

void Entity::update()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		if (components_[i]->isActive()) components_[i]->update();
	}
}

void Entity::lateUpdate()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		if (components_[i]->isActive()) components_[i]->lateUpdate();
	}
}

void Entity::OnCollision(Entity* other)
{int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		if (components_[i]->isActive()) components_[i]->OnCollision(other);
	}
}

Entity::~Entity()
{
	for (int i = 0; i < components_.size(); i++)
		components_[i].reset(nullptr);
}

bool Entity::hasComponent(const std::string& tag) {
	return (map_.find(tag) != map_.end());
}


void Entity::preupdate()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		if (components_[i]->isActive()) components_[i]->preupdate();
	}
}

void Entity::physicsUpdate()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		if (components_[i]->isActive()) components_[i]->physicsUpdate();
	}
}

void Entity::addComponentFromJson(json& args)
{
	string tag = args["type"];

	//if it doesn't exist, it's created
	if (!hasComponent(args["type"])) {
		Component* c(JsonFactoryParser::getInstance()->getComponentFromJSON(args["type"], args));
		if (c == nullptr)
			return;

		components_.push_back(uptr_cmp(c));
		map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
		c->setEntity(this);
		c->init(args);
	}
//if it already exists, it's being redefined (ideally only used with prefabs)
	else {
		map_[args["type"]]->redefine(args);
	}
}


void Entity::setName(const std::string& name) {
	name_ = name;
}

string const Entity::getName() {
	return name_;
}

void Entity::setTag(const std::string& tag)
{
	tag_ = tag;
}

string const Entity::getTag()
{
	return tag_;
}

void Entity::setEnabled(bool enabled) {
	enabled_ = enabled;

	if (activeOnHierarchy_) {
		for (auto& comp : components_)
			comp.get()->setActiveOnHierarchy(enabled);

		for (auto child : children_)
			child.second->setActiveOnHierarchy(enabled);
	}
}

void Entity::setActiveOnHierarchy(bool active) {
	activeOnHierarchy_ = active;

	if (!activeOnHierarchy_ || enabled_) {
		for (auto& comp : components_)
			comp.get()->setActiveOnHierarchy(active);

		for (auto child : children_)
			child.second->setActiveOnHierarchy(active);
	}
}

bool const Entity::isActive() {
	return enabled_ && activeOnHierarchy_;
}

const bool Entity::isEnabled()
{
	return enabled_;
}

const bool Entity::isActiveOnHierarchy()
{
	return activeOnHierarchy_;
}

Scene* Entity::getScene()
{
	return scene_;
}

Entity* Entity::getParent()
{
	return parent_;
}

std::map<string, Entity*>& Entity::getChildren()
{
	return children_;
}

Entity* Entity::getChild(std::string name)
{
	std::map<string, Entity*>::iterator child = children_.find(name);
	if (child != children_.end())
		return child->second;
	else
		return nullptr;
}

bool Entity::setParent(std::string name) {
	Entity* nParent = scene_->getEntity(name);
	if (nParent == nullptr)
		return false;

	if (parent_ != nullptr)
		parent_->getChildren().erase(name);

	nParent->getChildren()[name_] = this;

	parent_ = nParent;

	for (std::pair<string, Component*> comp : map_)
		comp.second->onSetParent(nParent);

	return true;
}

void Entity::clearParent() {
	if (parent_ == nullptr) return;

	parent_->getChildren().erase(name_);
	parent_ = nullptr;
}

void Entity::init(json& args) {
//Creates a transform component. Required by default.
	json modArgs = args;
	modArgs["type"] = "Transform";

	addComponentFromJson(modArgs);
}

bool Entity::ReceiveEvent(Event& event)
{
	//reenvia o mesaxe a todolos seus componentes
	for (auto c : map_) {
		if (c.second->ReceiveEvent(event))
			return true;
	}
	
	return false;
}

Transform* Entity::getTransform()
{
	return getComponent<Transform>("Transform");
}

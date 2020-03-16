#include "Entity.h"

#include <thread>
#include <chrono>
#include <algorithm>
#include <utility>
#include "Factory.h"
#include "Scene.h"
#include "JsonFactoryParser.h"
#include "Transform.h"

using namespace std;

Entity::Entity(Scene* scene, const std::string& name): scene(scene), name_(name)
{
	
}

void Entity::update()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		components_[i]->update();
	}
}

bool Entity::hasComponent(const std::string& tag) {
	return (map_.find(tag) != map_.end());
}

template<typename T>
T* Entity::getComponent(const std::string& tag)
{
	return static_cast<T*>(map_.find(tag));
}

void Entity::preupdate()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		components_[i]->preupdate();
	}
}

template<typename T>
T* Entity::addComponent(json& args)
{
	T* c(Factory::createComponent<T>(args));
	components_.push_back(uptr_cmp(c));
	map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
	c->setEntity(this);
	c->init();
	return c;
}

void Entity::addComponentFromJson(json& args)
{
	string tag = args["tag"];
//if it doesn't exist, it's created
	if (!hasComponent(args["tag"])) {
		Component* c(JsonFactoryParser::getInstance()->getComponentFromJSON(args["type"], args));
		if (c != nullptr)
		{
			components_.push_back(uptr_cmp(c));
			map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
			c->setEntity(this);
			c->init();
		}
	}
//if it already exists, it's being redefined (ideally only used with prefabs)
	else {
		map_[args["tag"]]->initFromJson(args);
	}
}

template<typename T>
void Entity::toggleComponent(const std::string& tag, bool state) {
	getComponent(tag).toggle(state);
}

void Entity::setName(const std::string& name) {
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

void Entity::init(json& args)
{
//Creates a transform component. Required by default.
	json modArgs = args;
	modArgs["tag"] = "Transform";

	addComponent<Transform>(modArgs);
}

bool Entity::ReceiveEvent(Event& event)
{
	//reenvia o mesaxe a todolos seus componentes
	for (auto c : map_) {
		EventManager::GetInstance()->ClearListeners(event.type);
		EventManager::GetInstance()->RegisterListener(c.second, event.type);
		EventManager::GetInstance()->EmitEvent(event);
		EventManager::GetInstance()->UnregisterListener(c.second, event.type);
	}
	
	return false;
}

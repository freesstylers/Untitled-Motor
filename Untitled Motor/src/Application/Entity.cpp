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


void Entity::preupdate()
{
	int length = components_.size();
	for (int i = 0; i < length; i++)
	{
		components_[i]->preupdate();
	}
}

void Entity::addComponentFromJson(json& args)
{
	string tag = args["type"];
//if it doesn't exist, it's created
	if (!hasComponent(args["type"])) {
		Component* c(JsonFactoryParser::getInstance()->getComponentFromJSON(args["type"], args));
		if (c != nullptr)
		{
			components_.push_back(uptr_cmp(c));
			map_.insert(std::pair<std::string, Component*>(c->getTag(), c));
			c->setEntity(this);
			c->init(args);
		}
	}
//if it already exists, it's being redefined (ideally only used with prefabs)
	else {
		map_[args["type"]]->initFromJson(args);
	}
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
	modArgs["type"] = "Transform";

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

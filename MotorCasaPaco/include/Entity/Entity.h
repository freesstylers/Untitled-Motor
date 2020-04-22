#pragma once
#include "Others/json.hpp"

#include <map>
#include <string>
#include <memory>
#include "Entity/Component.h"
#include "Entity/Factory.h"

using json = nlohmann::json;

class Scene;

#include "Events/EventListener.h"
#include "Events/EventManager.h"

using uptr_cmp = std::unique_ptr<Component>;

class Entity: public EventListener {
public:
	Entity(Scene* scene, const std::string& name);
	void start();
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();

	virtual ~Entity();

	template <typename T>
	T* getComponent(const std::string& tag) {
		if (!hasComponent(tag))
			return nullptr;
		return static_cast<T*>(map_[tag]);
	};

	void addComponentFromJson(json& args);

	bool hasComponent(const std::string& tag);

	template<typename T>
	void toggleComponent(const std::string& tag, bool state) {
		getComponent<T>(tag).toggle(state);
	};

	void setName(const std::string& name);
	std::string const getName();

	void setActive(bool state);
	bool const getActive();

	Scene* getScene();

	Entity* getParent();
	std::map<std::string, Entity*> getChildren();
	Entity* getChild(std::string name);

	bool setParent(std::string name);
	void clearParent();

	void init(json& args);
	
	bool ReceiveEvent(Event& event) override;

protected:

private:
	bool isActive_;
	std::string name_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;

	Entity* parent_ = nullptr;
	std::map<std::string, Entity*> children_;

	Scene* scene_;
};
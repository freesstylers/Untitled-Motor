#pragma once
#include <map>
#include <string>
#include <memory>

#include "Others/json.hpp"

#include "Entity/Component.h"
#include "Entity/Factory.h"

using json = nlohmann::json;

class Scene;
class Transform;

#include "Events/EventListener.h"
#include "Events/EventManager.h"

using uptr_cmp = std::unique_ptr<Component>;

class Entity: public EventListener {
public:
	Entity(Scene* scene, const std::string& name, const std::string& tag, const bool enabled = true);
	void preupdate();
	void physicsUpdate();
	void update();
	void lateUpdate();
	void pausedUpdate();
	void alwaysLateUpdate();

	void OnCollision(Entity* other);

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

	void setTag(const std::string& tag);
	std::string const getTag();

	/* DO NOT CALL MANUALLY, use 'setEnabled()' instead */
	void setActiveOnHierarchy(bool active);
	void setEnabled(bool active);

	const bool isActive();
	const bool isEnabled();
	const bool isActiveOnHierarchy();

	Scene* getScene();

	Entity* getParent();
	std::map<std::string, Entity*>& getChildren();
	Entity* getChild(std::string name);

	bool setParent(std::string name);
	void clearParent();

	void init(json& args);
	
	bool ReceiveEvent(Event& event) override;

	Transform* getTransform();

	bool DontDestroyOnLoad = false;
protected:

private:
	bool enabled_ = true, activeOnHierarchy_ = true;

	std::string name_;
	std::string tag_;
	std::vector<uptr_cmp> components_;
	std::map<std::string, Component*> map_;

	Entity* parent_ = nullptr;
	std::map<std::string, Entity*> children_;

	Scene* scene_;
};
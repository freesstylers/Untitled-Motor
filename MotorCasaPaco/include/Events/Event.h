#pragma once

#include <string>

enum EventType {
	TEXT,
	RIGIDBODY_INFO,
	RIGIDBODY_COLLISION,
	SETPARENT,
	RESET_GRAPHIC_INFO
};

class btRigidBody;
class btCollisionObject;

struct Event
{
public:
	inline Event(EventType id) {
		this->type = id;
	};

	EventType type;
};

struct TextEvent : public Event {
public:
	inline TextEvent(std::string text) : Event(EventType::TEXT) {
		this->text = text;
	};

	std::string text;
};

struct RigidBodyInfoEvent : public Event {
public:
	inline RigidBodyInfoEvent(btRigidBody* rb) : Event(EventType::RIGIDBODY_INFO) {
		this->rb = rb;
	}
	btRigidBody* rb;
};

class Entity;
struct RigidBodyCollisionEvent : public Event {
public:
	inline RigidBodyCollisionEvent(Entity* obj1, Entity* obj2) :Event(EventType::RIGIDBODY_COLLISION) {
		this->obj1 = obj1;
		this->obj2 = obj2;
	}
	Entity* obj1;
	Entity* obj2;
};

struct SetParentEvent : public Event {
public:
	inline SetParentEvent(Entity* parent) : Event(EventType::SETPARENT) {
		this->parent = parent;
	};

	Entity* parent;
};
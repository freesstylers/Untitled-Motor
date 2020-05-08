#pragma once

#include <string>

class btRigidBody;
class btCollisionObject;

struct Event
{
public:
	inline Event(std::string id) {
		this->type = id;
	};

	std::string type;
};

struct TextEvent : public Event {
public:
	inline TextEvent(std::string text) : Event("TEXT") {
		this->text = text;
	};

	std::string text;
};

struct BoolEvent : public Event {
public:
	inline BoolEvent(std::string id, bool flag) : Event(id) {
		this->flag = flag;
	};

	bool flag;
};

struct RigidBodyInfoEvent : public Event {
public:
	inline RigidBodyInfoEvent(btRigidBody* rb) : Event("RIGIDBODY_INFO") {
		this->rb = rb;
	}
	btRigidBody* rb;
};

class Entity;
struct RigidBodyCollisionEvent : public Event {
public:
	inline RigidBodyCollisionEvent(Entity* obj1, Entity* obj2) :Event("RIGIDBODY_COLLISION") {
		this->obj1 = obj1;
		this->obj2 = obj2;
	}
	Entity* obj1;
	Entity* obj2;
};
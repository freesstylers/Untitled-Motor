#pragma once

#include <string>
#include "btBulletCollisionCommon.h"

enum EventType {
	TEXT,
	RIGIDBODY_INFO,
	RIGIDBODY_COLLISION
};

class btRigidBody;

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

struct RigidBodyCollisionEvent : public Event {
public:
	inline RigidBodyCollisionEvent(const btCollisionObject* obj1, const btCollisionObject* obj2) :Event(EventType::RIGIDBODY_COLLISION) {
		this->obj1 = obj1;
		this->obj2 = obj2;
	}
	const btCollisionObject* obj1;
	const btCollisionObject* obj2;
};
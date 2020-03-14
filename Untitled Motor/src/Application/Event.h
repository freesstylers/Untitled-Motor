#pragma once

#include <string>

enum EventType {
	TEXT,
	RIGIDBODY_INFO
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
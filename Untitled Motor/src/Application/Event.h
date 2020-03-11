#pragma once

#include <string>

enum EventType {
	TEXT,
};

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
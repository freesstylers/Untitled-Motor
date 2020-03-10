#pragma once

#include <string>

enum EventID {
	Text,
};

struct Event
{
public:
	inline Event(EventID id) {
		this->id = id;
	};

	EventID id;
};

struct TextEvent : public Event {
public:
	inline TextEvent(std::string text) : Event(EventID::Text) {
		this->text = text;
	};

	std::string text;
};
#pragma once
#include "Entity/Component.h"

class TestComponent : public Component
{
public:
	TestComponent(json& args);
	~TestComponent() override;

	void start() override;
	void onActivated() override;
	bool ReceiveEvent(Event& event) override;
	void update() override;

	int value = 0;

private:
	Entity* refEntity = nullptr;
	std::string refEntityName;
};


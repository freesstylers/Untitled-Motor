#pragma once
#ifndef CHANGEVSYNCCOMPONENT_H
#define CHANGEVSYNCCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class ChangeVSyncComponent : public Component
{

public:
	ChangeVSyncComponent(json& args);
	~ChangeVSyncComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);
	bool ReceiveEvent(Event& event) override;

private:
	CEGUI::Window* textToChange;
};

#endif


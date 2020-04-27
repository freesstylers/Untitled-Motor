#pragma once
#ifndef APPLYGRAPHICCHANGESCOMPONENT_H
#define APPLYGRAPHICCHANGESCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"


class ApplyGraphicChangesComponent : public Component
{

public:
	ApplyGraphicChangesComponent(json& args);
	~ApplyGraphicChangesComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);

private:

};

#endif


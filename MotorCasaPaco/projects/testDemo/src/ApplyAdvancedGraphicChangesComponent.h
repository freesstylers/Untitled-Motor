#pragma once
#ifndef APPLYADVANCEDGRAPHICCHANGESCOMPONENT_H
#define APPLYADVANCEDGRAPHICCHANGESCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"


class ApplyAdvancedGraphicChangesComponent : public Component
{

public:
	ApplyAdvancedGraphicChangesComponent(json& args);
	~ApplyAdvancedGraphicChangesComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);

private:

};

#endif


#pragma once
#ifndef REVERTADVANCEDGRAPHICCHANGESCOMPONENT_H
#define REVERTADVANCEDGRAPHICCHANGESCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"


class RevertAdvancedGraphicChangesComponent : public Component
{

public:
	RevertAdvancedGraphicChangesComponent(json& args);
	~RevertAdvancedGraphicChangesComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);

private:
	CEGUI::Window* fsaa;
	CEGUI::Window* shadows;
	CEGUI::Window* gamma;
};

#endif


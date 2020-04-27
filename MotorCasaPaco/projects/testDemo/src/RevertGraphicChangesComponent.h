#pragma once
#ifndef REVERTGRAPHICCHANGESCOMPONENT_H
#define REVERTGRAPHICCHANGESCOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"


class RevertGraphicChangesComponent : public Component
{

public:
	RevertGraphicChangesComponent(json& args);
	~RevertGraphicChangesComponent();
	void init(json& j) override;
	bool function(const CEGUI::EventArgs& e);

private:
	CEGUI::Window* fullscreen;
	CEGUI::Window* resolution;
	CEGUI::Window* screenProportion;
	CEGUI::Window* vsync;

};

#endif


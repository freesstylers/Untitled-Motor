#pragma once
#ifndef FORMATRESOLUTIONCHANGECOMPONENT_H
#define FORMATRESOLUTIONCHANGECOMPONENT_H
#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"


class FormatResolutionChangeComponent : public Component
{

public:
	FormatResolutionChangeComponent(json& args);
	~FormatResolutionChangeComponent();
	void init(json& j) override;
	bool functionResLess(const CEGUI::EventArgs& e);
	bool functionResMore(const CEGUI::EventArgs& e);

	bool functionForLess(const CEGUI::EventArgs& e);
	bool functionForMore(const CEGUI::EventArgs& e);

private:

	int getCurrentPos(std::string currentFormat_, std::string currentRes_);

	CEGUI::Window* ResText;
	CEGUI::Window* ForText;
	std::string currentFormat;
	std::string currentRes;
	int currentPos;
	
	std::vector<std::vector<std::string>> resolutions;


};

#endif


#pragma once
#include <json.hpp>

#include "Component.h"

using json = nlohmann::json;

class BaseFactory
{
public:
	BaseFactory() {};

	virtual Component* createComponent(json& args) = 0;
};
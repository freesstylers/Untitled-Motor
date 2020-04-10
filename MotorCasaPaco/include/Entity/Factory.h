#pragma once

#include "Entity/Component.h"

#include "Others/json.hpp"
using json = nlohmann::json;

class BaseFactory
{
public:
	BaseFactory() {};

	virtual Component* createComponent(json& args) = 0;
};
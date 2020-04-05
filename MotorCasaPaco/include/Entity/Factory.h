#pragma once
#include "Others/json.hpp"

#include "Entity/Component.h"

using json = nlohmann::json;

class BaseFactory
{
public:
	BaseFactory() {};

	virtual Component* createComponent(json& args) = 0;
};
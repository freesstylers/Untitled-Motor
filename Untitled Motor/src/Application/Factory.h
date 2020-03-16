#pragma once
#include <json.hpp>

#include "Component.h"

using json = nlohmann::json;

class Factory
{
public:
	template<typename T>
	static T* createComponent(json& args) {
		return new T(args);
	};
private:
	Factory();
};
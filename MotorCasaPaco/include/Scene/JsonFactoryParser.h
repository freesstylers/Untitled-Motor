#pragma once

#include <map>

#include "Others/json.hpp"
#include "Entity/Component.h"
#include "Entity/Factory.h"

using json = nlohmann::json;

class JsonFactoryParser
{
public:
	typedef std::function<Component* (const std::string&, json&)> ComponentCallback;

	~JsonFactoryParser();

	static JsonFactoryParser* getInstance();
	static bool setupInstance();
	static void clean();

	Component* getComponentFromJSON(const std::string& type, json& args);

	void addFactory(const std::string& type, BaseFactory* f);

private:
	JsonFactoryParser();
	static JsonFactoryParser* instance;

	std::map<std::string, BaseFactory*> map;
};


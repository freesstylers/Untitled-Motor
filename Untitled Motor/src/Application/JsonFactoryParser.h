#pragma once
#include <json.hpp>
#include "Component.h"

#include "Factory.h"
#include <map>

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


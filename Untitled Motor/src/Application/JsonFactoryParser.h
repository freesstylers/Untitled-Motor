#pragma once
#include <json.hpp>
#include "Component.h"
#include <functional>

using json = nlohmann::json;

Component* defaultCallback(const std::string& name, json& j);

class JsonFactoryParser
{
public:
	typedef std::function<Component* (const std::string&, json&)> ComponentCallback;

	~JsonFactoryParser();

	static JsonFactoryParser* getInstance();
	static bool setupInstance();
	static void clean();

	Component* getComponentFromJSON(const std::string& type, json& j);



	void addExtraCallback(ComponentCallback& c);
	ComponentCallback getExtraCallback();


private:
	JsonFactoryParser();
	static JsonFactoryParser* instance;

	ComponentCallback extraCallback;
};


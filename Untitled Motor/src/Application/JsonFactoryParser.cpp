#include "JsonFactoryParser.h"

#include "Factory.h"

#include "TestComponent.h"
#include "Transform.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "MarbleMovementTest.h"

JsonFactoryParser* JsonFactoryParser::instance = 0;

Component* defaultCallback(const std::string& name, json& j)
{
	return nullptr;
}

JsonFactoryParser::JsonFactoryParser() {
	extraCallback = defaultCallback;
}

JsonFactoryParser::~JsonFactoryParser()
{
}

JsonFactoryParser* JsonFactoryParser::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool JsonFactoryParser::setupInstance()
{
	if (instance == 0)
	{
		instance = new JsonFactoryParser();
		return true;
	}

	return false;
}

void JsonFactoryParser::clean()
{
	delete instance;
}

Component* JsonFactoryParser::getComponentFromJSON(const std::string& type, json& j)
{
	if (type == "Transform")
		return Factory::createComponent<Transform>(j);
	else if (type == "Mesh")
		return Factory::createComponent<Mesh>(j);
	else if (type == "RigidBody")
		return Factory::createComponent<RigidBody>(j);
	else if (type == "TestComponent")
		return Factory::createComponent<TestComponent>(j);
	else if (type == "MarbleMovementTest")
		return Factory::createComponent<MarbleMovementTest>(j);
	else
		return extraCallback(type, j);
}

void JsonFactoryParser::addExtraCallback(ComponentCallback& c)
{
	extraCallback = c;
}

JsonFactoryParser::ComponentCallback JsonFactoryParser::getExtraCallback()
{
	return extraCallback;
}

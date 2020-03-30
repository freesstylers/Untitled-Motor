#include "JsonFactoryParser.h"

#include "Factory.h"
#include "TestComponent.h"
#include "Transform.h"
#include "Mesh.h"
#include "RigidBody.h"
#include "MarbleMovementTest.h"
#include "TerrainRotation.h"

JsonFactoryParser* JsonFactoryParser::instance = 0;

JsonFactoryParser::JsonFactoryParser() {

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

Component* JsonFactoryParser::getComponentFromJSON(const std::string& type, json& args)
{
	std::map<std::string, BaseFactory*>::iterator it = map.find(type);
	if (it != map.end())
		return (*it).second->createComponent(args);
	return nullptr;
}

void JsonFactoryParser::addFactory(const std::string& type, BaseFactory* f)
{
	map[type] = f;
}
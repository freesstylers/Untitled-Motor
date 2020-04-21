#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "GUI/GUI_Manager.h"
#include "Menu.h"

#include "Scene/JsonFactoryParser.h"

#include "SimpleMovement.h"
#include "TerrainRotation.h"
#include "ChangeSceneButtonComponent.h"

class SimpleMovementFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new SimpleMovement(args);
	};
};
class TerrainRotationFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new TerrainRotation(args);
	};
};

class ChangeSceneButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeSceneButtonComponent(args);
	};
};

MotorCasaPaco* motorCasaPaco;

#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try { MotorCasaPaco::setupInstance("Motor Casa Paco"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("Motor Casa Paco init fail \n" + std::string(e.what()) + "\n");	return 0;
	}

	motorCasaPaco = MotorCasaPaco::getInstance();

	try
	{
		motorCasaPaco->init();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		delete motorCasaPaco;
		return 0;
	}

	JsonFactoryParser::getInstance()->addFactory("SimpleMovement", new SimpleMovementFactory());
	JsonFactoryParser::getInstance()->addFactory("TerrainRotation", new TerrainRotationFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());

	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("A_Toda_Pastilla.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("A_Toda_Pastilla/Mouse_Arrow");

	motorCasaPaco->changeScene("test");
	/*
	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("A_Toda_Pastilla.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->loadLayout("Menu.layout");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("A_Toda_Pastilla/Mouse_Arrow");


	CEGUI::PushButton* b = motorCasaPaco->getGUI_Manager()->getInstance()->getPushButton("MainMenu/Play");

	Menu* men = new Menu(motorCasaPaco->getGUI_Manager());
	men->setEvent(0, b);
	*/

	//motorCasaPaco->getGUI_Manager()->getInstance()->setEvents(b, &test, this);
	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(motorCasaPaco->getGUI_Manager()->getInstance()->getRoot()->getChild("MainMenu/Play"));
	//CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(motorCasaPaco->getGUI_Manager()->getInstance()->getRoot()->getChild("MainMenu/Play"));

	motorCasaPaco->start();

	delete motorCasaPaco;

	return 0;
}
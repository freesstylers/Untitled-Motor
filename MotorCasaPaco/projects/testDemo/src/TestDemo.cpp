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
#include "ExitButtonComponent.h"
#include "ChangeFullScreenComponent.h"
#include "FormatResolutionChangeComponent.h"
#include "ApplyGraphicChangesComponent.h"
#include "ChangeVyncComponent.h"
#include "FSAAChangeComponent.h"
#include "ApplyAdvancedGraphicChangesComponent.h"
#include "RevertGraphicChangesComponent.h"
#include "TestComponent.h"

#include "RevertAdvancedGraphicChangesComponent.h"
#include "ChangeGammaComponent.h"
#include "ChangeGraphicSceneComponent.h"

#include "MainMenuInputComponent.h"
#include "OptionsMenuInputComponent.h"

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

class ExitButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ExitButtonComponent(args);
	};
};

class ChangeFullScreenComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeFullScreenComponent(args);
	};
};

class FormatResolutionChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FormatResolutionChangeComponent(args);
	};
};

class ApplyGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyGraphicChangesComponent(args);
	};
};

class ChangeVSyncComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeVSyncComponent(args);
	};
};

class FSAAChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FSAAChangeComponent(args);
	};
};

class ApplyAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyAdvancedGraphicChangesComponent(args);
	};
};

class RevertGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertGraphicChangesComponent(args);
	};
};

class RevertAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertAdvancedGraphicChangesComponent(args);
	};
};

class ChangeGammaComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGammaComponent(args);
	};
};

class ChangeGraphicSceneComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGraphicSceneComponent(args);
	};
};

class TestComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new TestComponent(args);
	};
};

class MainMenuInputComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MainMenuInputComponent(args);
	};
};

class OptionsMenuInputComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new OptionsMenuInputComponent(args);
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
	JsonFactoryParser::getInstance()->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeFullScreenComponent", new ChangeFullScreenComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("FormatResolutionChangeComponent", new FormatResolutionChangeComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ApplyGraphicChangesComponent", new ApplyGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeVSyncComponent", new ChangeVSyncComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("FSAAChangeComponent", new FSAAChangeComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ApplyAdvancedGraphicChangesComponent", new ApplyAdvancedGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("RevertGraphicChangesComponent", new RevertGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("RevertAdvancedGraphicChangesComponent", new RevertAdvancedGraphicChangesComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeGammaComponent", new ChangeGammaComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("ChangeGraphicSceneComponent", new ChangeGraphicSceneComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("TestComponent", new TestComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("MainMenuInputComponent", new MainMenuInputComponentFactory());
	JsonFactoryParser::getInstance()->addFactory("OptionsMenuInputComponent", new OptionsMenuInputComponentFactory());

	MotorCasaPaco::getInstance()->getGUI_Manager()->loadScheme("A_Toda_Pastilla.scheme");
	MotorCasaPaco::getInstance()->getGUI_Manager()->setMouseCursor("A_Toda_Pastilla/Mouse_Arrow");

	motorCasaPaco->start("test");

	MotorCasaPaco::clean();

	return 0;
}
#include "GUI/GUI_Manager.h"

#include "MotorCasaPaco.h"
#include <iostream>

GUI_Manager* GUI_Manager::instance = 0;

GUI_Manager::GUI_Manager(Ogre::RenderWindow* window)
{
	CEGUI::OgreRenderer& aux = CEGUI::OgreRenderer::bootstrapSystem(*MotorCasaPaco::getInstance()->getOgreWin());
	renderer = &aux;

	setupResources();

	createRoot();
	initResources(0);

	setMouseCursor("AlfiskoSkin/MouseArrow");
	//hideMouseCursor();
	
	
	//Callbacks?
}

bool GUI_Manager::TestButtonFunction(const CEGUI::EventArgs& e)
{
	std::cout << "Boton funcional\n";
	return true;
}

GUI_Manager::~GUI_Manager()
{
	renderer->destroySystem();
}

GUI_Manager* GUI_Manager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

void GUI_Manager::createRoot()
{
	CEGUI::WindowManager& a = CEGUI::WindowManager::getSingleton();
	winManager = &a;
	
	root = new GUI_Element(a.createWindow("DefaultWindow", "root"));
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root->getWindowElement());
}

void GUI_Manager::loadLayout(CEGUI::String filename)
{
	try
	{
		CEGUI::WindowManager::getSingleton().loadLayoutFromFile(filename);
	}
	catch (std::exception e)
	{
		//Javi, las excepciones
	}
}

void GUI_Manager::setupDefaultResources()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

void GUI_Manager::initResources(int code)
{
	switch (code)
	{
		case 1:
			break;


		default: //De momento se cargan estos, para poder elegir en funcion del juego (se puede cargar de archivo incluso?)

			//Schemes
			CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("AlfiskoSkin.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");

			//Mouse Cursor
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
			//CEGUI::System::getSingleton().getDefaultGUIContext().

			//Fonts
			CEGUI::FontManager::getSingleton().createFreeTypeFont("Batang", 16, true, "batang.ttf");


			//CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");



			break;
	}
/*#ifdef _DEBUG
	fpsText = new UIElement(root->getElement()->createChild("TaharezLook/StaticText", "FPSText"));
	fpsText->setPosition(0.9f, 0.0f);
	fpsText->setSize(0.1f, 0.1f);
#endif*/
}

CEGUI::System& GUI_Manager::getSystem()
{
	CEGUI::System& aa = CEGUI::System::getSingleton();

	return aa;
}

void GUI_Manager::update(float deltaTime)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().injectTimePulse(deltaTime);

	//Mas cosas a a�adir
}

void GUI_Manager::addChild(int type, std::string name)
{
	switch (type)
	{
	case 0: //Layout
	{
		CEGUI::Window* layout = winManager->getSingleton().loadLayoutFromFile(name); //Habria que a�adir el archivo del que proceden como opcion, en caso de usar mas de uno?
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(layout);
	    root->addChild(layout);
	}
		break;
	case 1:
	{
		CEGUI::PushButton* testButton = static_cast<CEGUI::PushButton*>(winManager->getSingleton().createWindow("TaharezLook/Button", name));
		testButton->setText("Hello World!");
		testButton->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5, 0.5), CEGUI::UDim(0.5, 0.5)));
		testButton->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0.15), CEGUI::UDim(0.15, 0.15)));		
		testButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GUI_Manager::TestButtonFunction, this)); //Esto no va, fijo que es cosa del this
		CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(testButton);
		root->addChild(testButton);
	}
		break;
	default:
	{
	
	}
		break;
	}
}

void GUI_Manager::setMouseCursor(const std::string& imageFile)
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(imageFile);
}

void GUI_Manager::showMouseCursor()
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
}

void GUI_Manager::hideMouseCursor()
{
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().hide();
}

bool GUI_Manager::setupInstance(Ogre::RenderWindow* window)
{
	if (instance == 0)
	{
		instance = new GUI_Manager(window);
		return true;
	}

	return false;
}

void GUI_Manager::setupResources()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

void GUI_Manager::clean()
{
	delete instance;
}

#include "UIManager.h"

UIManager* UIManager::instance = 0;

UIManager::UIManager(Ogre::RenderWindow* window)
{
	CEGUI::OgreRenderer& aux = CEGUI::OgreRenderer::bootstrapSystem(*window);
	renderer = &aux;

	setupResources();
	createRoot();

	//Callbacks
}

UIManager::~UIManager()
{
	//renderer->destroySystem();
}

UIManager* UIManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

void UIManager::createRoot()
{
	CEGUI::Window* aux; 
	aux = CEGUI::WindowManager::getSingleton().createWindow("Default", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(aux);
}

void UIManager::loadLayout(CEGUI::String filename)
{
	try {
		CEGUI::WindowManager::getSingleton().loadLayoutFromFile(filename);
	}
	catch (std::exception e)
	{
		//Javi, las excepciones
	}
}

void UIManager::setupDefaultResources()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

void UIManager::initResources(int code)
{
	switch (code)
	{
		case 1:
			break;
		default:
			//Schemes
			CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
			CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");

			//Mouse Cursor
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

			//Fonts
			CEGUI::FontManager::getSingleton().createFreeTypeFont("Batang", 16, true, "batang.ttf");
			break;
	}

	/*
#ifdef _DEBUG
	fpsText = new UIElement(root->getElement()->createChild("TaharezLook/StaticText", "FPSText"));
	fpsText->setPosition(0.9f, 0.0f);
	fpsText->setSize(0.1f, 0.1f);
#endif
	*/
}


bool UIManager::setupInstance(Ogre::RenderWindow* window)
{
	if (instance == 0)
	{
		instance = new UIManager(window);
		return true;
	}

	return false;
}

void UIManager::setupResources()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

void UIManager::clean()
{
	//delete instance;
	//UIManager::renderer
	//renderer->destroySystem();
}

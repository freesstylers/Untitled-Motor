#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

UIManager* UIManager::getInstance()
{

}

void UIManager::createRoot()
{
	CEGUI::Window* aux; 
	aux = CEGUI::WindowManager::getSingleton().createWindow("Default", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(root);
}


bool UIManager::setupInstance(Ogre::RenderWindow* window)
{
	CEGUI::OgreRenderer& aux = CEGUI::OgreRenderer::bootstrapSystem(*window);
	renderer = &aux;	

	setupResources();
	createRoot();

	//Callbacks
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
	renderer->destroySystem();
}

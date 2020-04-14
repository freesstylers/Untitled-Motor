#pragma once

#include <CEGUI/Event.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>
#include "GUI/GUI_Element.h"

class GUI_Manager
{
public:
	~GUI_Manager();

	static GUI_Manager* getInstance();
	static bool setupInstance(Ogre::RenderWindow* window);
	void setupResources();
	static void clean();
	void createRoot();
	void loadLayout(CEGUI::String filename);
	void setupDefaultResources();
	void initResources(int code);
	CEGUI::System& getSystem();
	void update(float deltaTime);
	void addChild(int type, std::string name);
	void setMouseCursor(const std::string& imageFile);
	void showMouseCursor();
	void hideMouseCursor();
	bool test(const CEGUI::EventArgs& e);

	GUI_Element* getRoot();
	CEGUI::WindowManager* getWinManager();

private:
	GUI_Manager(Ogre::RenderWindow* window);
	

	static GUI_Manager* instance;
	CEGUI::OgreRenderer* renderer;
	GUI_Element* root;
	CEGUI::WindowManager* winManager;
};


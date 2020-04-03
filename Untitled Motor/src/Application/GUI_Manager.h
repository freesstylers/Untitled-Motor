#pragma once

#include <CEGUI/Event.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>

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

private:
	GUI_Manager(Ogre::RenderWindow* window);

	static GUI_Manager* instance;
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* root;
};


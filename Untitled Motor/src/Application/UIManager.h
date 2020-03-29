#pragma once

#include <CEGUI/Event.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <OgreRenderWindow.h>

class UIManager
{
public:
	~UIManager();

	static UIManager* getInstance();
	static bool setupInstance(Ogre::RenderWindow* window);
	void setupResources();
	static void clean();
	void createRoot();
	void loadLayout(CEGUI::String filename);
	void setupDefaultResources();
	void initResources(int code);

private:
	UIManager(Ogre::RenderWindow* window);

	static UIManager* instance;
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* root;
};


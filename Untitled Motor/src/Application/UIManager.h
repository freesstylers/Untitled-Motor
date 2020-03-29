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
	bool setupInstance(Ogre::RenderWindow* window);
	void setupResources();
	void clean();
	void createRoot();

private:
	UIManager();

	static UIManager* instance;
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* root;
};


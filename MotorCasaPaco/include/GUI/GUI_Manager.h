#pragma once
#include "GUI/GUI_Element.h"

namespace CEGUI {
	class String;
	class System;
	class EventArgs;
	class OgreRenderer;
	class WindowManager;
	class PushButton;
	class EventArgs;
	class Window;
}

namespace Ogre {
	class RenderWindow;
}

class GUI_Manager
{
public:
	~GUI_Manager();

	static GUI_Manager* getInstance();
	static bool setupInstance(Ogre::RenderWindow* window);
	void setupResources();
	static void clean();
	void clear();
	void createRoot();
	void loadLayout(std::string filename);
	void loadScheme(std::string filename);
	CEGUI::System& getSystem();
	void update(float deltaTime);
	void addChild(int type, std::string name);
	CEGUI::PushButton* getPushButton(std::string name);
	CEGUI::Window* getWindow(std::string name);
	CEGUI::Window* getStaticText(std::string name);
	void changeText(CEGUI::Window* window, std::string text);
	void appendText(CEGUI::Window* window, std::string text, bool space);
	void setMouseCursor(const std::string& imageFile);
	void showMouseCursor();
	void hideMouseCursor();
	bool test(const CEGUI::EventArgs& e);
	void updateScreenSize(int width, int height);
	void setEvents(CEGUI::PushButton* button, std::function<bool(const CEGUI::EventArgs&)> function);
	void loadFont(std::string name);
	void setupDefaultResources();
	void setDefaultFont(int value);
	GUI_Element* getRoot();
	CEGUI::WindowManager* getWinManager();
	void injectPosition(int x, int y);
	void injectLeftMouseButtonDown();
	void injectLeftMouseButtonUp();

private:
	GUI_Manager(Ogre::RenderWindow* window);

	static GUI_Manager* instance;
	CEGUI::OgreRenderer* renderer;
	GUI_Element* root;
	CEGUI::WindowManager* winManager;
};


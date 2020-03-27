#pragma once

#include <OgreFileSystemLayer.h>
#include "SGTechniqueResolverListener.h"
#include <OgreRTShaderSystem.h>
#include <json.hpp>

using json = nlohmann::json;

class ResourceManager	//carga de recursos (por ahora)
{
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	static bool setupInstance(const Ogre::String& path);
	static void clean();

	void setup();

	void addSceneManager(Ogre::SceneManager* sm);

	json loadSceneFile(const Ogre::String& sceneName);

private:
	ResourceManager(const Ogre::String& path);

	void locateOgreResources();
	void loadOgreResources();


	void loadPrefabFile(const Ogre::String& fileDir);

	bool initRTShaderSystem();
	void wipeRTShaderSystem();

	Ogre::FileSystemLayer* FSLayer;
	Ogre::String path;
	Ogre::String RTShaderLibPath;

	json prefabs;


	Ogre::RTShader::ShaderGenerator* shaderGenerator;
	SGTechniqueResolverListener* materialMgrListener;

	static ResourceManager* instance;
};


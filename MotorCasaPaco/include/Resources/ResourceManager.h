#pragma once

#include "Others/json.hpp"

#include <OgreFileSystemLayer.h>
#include <OgreRTShaderSystem.h>

using json = nlohmann::json;

class SGTechniqueResolverListener;

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

	json getPrefabs();

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


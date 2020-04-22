#pragma once

#include "Others/json.hpp"

namespace Ogre {
	class FileSystemLayer;
	namespace RTShader {
		class ShaderGenerator;
	};
	class SceneManager;
}

using json = nlohmann::json;

class SGTechniqueResolverListener;

class ResourceManager	//carga de recursos (por ahora)
{
public:
	~ResourceManager();

	static ResourceManager* getInstance();
	static bool setupInstance(const std::string& path);
	static void clean();

	void setup();

	void addSceneManager(Ogre::SceneManager* sm);

	json loadSceneFile(const std::string& sceneName);

	json getPrefabs();

private:
	ResourceManager(const std::string& path);

	void locateOgreResources();
	void loadOgreResources();


	void loadPrefabFile(const std::string& fileDir);

	bool initRTShaderSystem();
	void wipeRTShaderSystem();

	Ogre::FileSystemLayer* FSLayer;
	std::string path;
	std::string RTShaderLibPath;

	json prefabs;


	Ogre::RTShader::ShaderGenerator* shaderGenerator = nullptr;
	SGTechniqueResolverListener* materialMgrListener = nullptr;

	static ResourceManager* instance;
};


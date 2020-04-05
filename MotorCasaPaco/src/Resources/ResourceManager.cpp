#include "Resources/ResourceManager.h"

#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreResourceGroupManager.h>
#include <OgreTextureManager.h>
#include <iostream>

ResourceManager* ResourceManager::instance = 0;

ResourceManager* ResourceManager::getInstance()
{
	if (instance == 0 || instance == nullptr)
	{
		return nullptr;
	}

	return instance;
}

bool ResourceManager::setupInstance(const Ogre::String& path)
{
	if (instance == 0)
	{
		instance = new ResourceManager(path);
		return true;
	}

	return false;
}

void ResourceManager::clean()
{
	delete instance;
}

ResourceManager::ResourceManager(const Ogre::String& path) : path(path)
{
	FSLayer = new Ogre::FileSystemLayer(path);
}


ResourceManager::~ResourceManager()
{
	delete FSLayer;

	wipeRTShaderSystem();
}

void ResourceManager::setup()
{
	locateOgreResources();
	initRTShaderSystem();
	loadOgreResources();

	loadPrefabFile(path + "prefabs.json");
}

void ResourceManager::addSceneManager(Ogre::SceneManager* sm)
{
	shaderGenerator->addSceneManager(sm);
}

json ResourceManager::loadSceneFile(const Ogre::String& sceneName)
{
	json j;
	std::ifstream i(path + "scenes/" + sceneName + ".json");

	if (i.is_open())
	{
		i >> j;
		i.close();
	}
	else
	{
		std::cout << "File not found: " << path << "scenes/" << sceneName << ".json" << "\n";
	}

	return j;
}

json ResourceManager::getPrefabs()
{
	return prefabs;
}

void ResourceManager::locateOgreResources()
{
	// load resource paths from config file
	Ogre::ConfigFile cf;

	Ogre::String resourcesPath = FSLayer->getConfigFilePath("resources.cfg");
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(path + "ogre"),
			"FileSystem", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	}

	Ogre::String sec, type, arch;
	// go through all specified resource groups
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci) {
		sec = seci->first;
		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// go through all resource paths
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
		}
	}

	sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	OgreAssert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	arch = genLocs.front().archive->getName();
	type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/shaders/programs/HLSL", type, sec);
	}

	RTShaderLibPath = arch + "/shaders/programs/RTShaderLib";
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(RTShaderLibPath + "/materials", type, sec);

	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(RTShaderLibPath + "/GLSL", type, sec);
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(RTShaderLibPath + "/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(RTShaderLibPath + "/GLSL", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(RTShaderLibPath + "/HLSL", type, sec);
	}
}

bool ResourceManager::initRTShaderSystem()
{
	if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		shaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
		// Core shader libs not found -> shader generating will fail.
		if (RTShaderLibPath.empty())
			return false;
		// Create and register the material manager listener if it doesn't exist yet.
		if (!materialMgrListener) {
			materialMgrListener = new SGTechniqueResolverListener(shaderGenerator);
			Ogre::MaterialManager::getSingleton().addListener(materialMgrListener);
		}
	}

	return true;
}

void ResourceManager::wipeRTShaderSystem()
{
	// Restore default scheme.
	Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);

	// Unregister the material manager listener.
	if (materialMgrListener != nullptr)
	{
		Ogre::MaterialManager::getSingleton().removeListener(materialMgrListener);
		delete materialMgrListener;
		materialMgrListener = nullptr;
	}

	// Destroy RTShader system.
	if (shaderGenerator != nullptr)
	{
		Ogre::RTShader::ShaderGenerator::destroy();
		shaderGenerator = nullptr;
	}
}

void ResourceManager::loadOgreResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void ResourceManager::loadPrefabFile(const Ogre::String& fileDir)
{
	std::ifstream i(fileDir);

	if (i.is_open())
	{
		i >> prefabs;
		i.close();
	}
	else
	{
		std::cout << "File not found: " << fileDir << "\n";
	}

}

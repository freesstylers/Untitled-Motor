#pragma once
#include "Component.h"
#include "OgreSceneManager.h"
#include "OgreEntity.h"

class RenderComponent : public Component
{
public:
	RenderComponent(std::string tag, Ogre::SceneManager* sM, std::string mesh, std::string material = "", Ogre::SceneNode* father=nullptr);
	virtual void update();
	Ogre::Entity* getOgreEntity() { return ent; };
	Ogre::SceneNode* getNode() { return node; };
protected:
	Ogre::SceneManager* sceneManager=nullptr;
	Ogre::SceneNode* node = nullptr;
	Ogre::Entity* ent = nullptr;
};
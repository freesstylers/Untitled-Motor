#pragma once
#include <Ogre.h>
#include "Component.h"
#include "EventListener.h"



class Transform :
	public Component, public EventListener
{
public:
	Transform(json& args);

private:
	bool ReceiveEvent(Event& event) override;

	Ogre::Vector3 position;
	Ogre::Vector3 rotation;
	Ogre::Vector3 scale;
	Ogre::SceneNode* node;
};


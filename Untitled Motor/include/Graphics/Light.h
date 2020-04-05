#pragma once
#include "Entity/Component.h"

#include <Ogre.h>

class Light :
	public Component
{
public:
	Light(json& args);
	~Light() override;
	void init(json& args) override;
	void redefine(json& args) override;

private:
	Ogre::Light* light;
};


#pragma once
#include "Entity/Component.h"
#include <string>

namespace Ogre {
	class ParticleSystem;
}

class ParticleSystem :
	public Component
{
public:
	ParticleSystem(json& args);
	void init(json& args) override;
	void redefine(json& args) override;
	void onActivated() override;
	void onDeactivated() override;
	~ParticleSystem() override;

private:
	Ogre::ParticleSystem* ogrePSystem_ = nullptr;
	std::string ogrePSystemName_, ogrePSystemTemplate_;

};


#include "Graphics/ParticleSystem.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

#include <MotorCasaPaco.h>
#include "Entity/Transform.h"

ParticleSystem::ParticleSystem(json& args) : Component(args)
{

}

void ParticleSystem::init(json& args)
{
	if (!args["name"].is_null()) {
		std::string aux = args["name"];
		ogrePSystemName_ = aux;
	}

	if (!args["template"].is_null()) {
		std::string aux = args["template"];
		ogrePSystemTemplate_ = aux;
	}

	ogrePSystem_ = MotorCasaPaco::getInstance()->getSM()->createParticleSystem(ogrePSystemName_, ogrePSystemTemplate_);
	e_->getTransform()->getNode()->attachObject(ogrePSystem_);
}

void ParticleSystem::redefine(json& args)
{
}

void ParticleSystem::onActivated()
{
}

void ParticleSystem::onDeactivated()
{
}

ParticleSystem::~ParticleSystem()
{
	ogrePSystem_->clear();
	ogrePSystem_->detachFromParent();
	MotorCasaPaco::getInstance()->getSM()->destroyParticleSystem(ogrePSystemName_);
	ogrePSystem_ = nullptr;
}

#include "Graphics/ParticleSystem.h"

#include <OgreSceneManager.h>
#include <OgreParticleSystem.h>

#include <MotorCasaPaco.h>
#include "Entity/Transform.h"
#include "Scene/Scene.h"

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

	if (!args["timeLimit"].is_null()) {
		float aux = args["timeLimit"];
		timeLimit_ = aux;
	}

	if (!args["destroyOnTimeLimit"].is_null()) {
		bool aux = args["destroyOnTimeLimit"];
		destroyOnTimeLimit_ = aux;
	}

	ogrePSystemFixedName_ = ogrePSystemName_;
	int i = 1;
	while (MotorCasaPaco::getInstance()->getSM()->hasParticleSystem(ogrePSystemFixedName_)) {
		ogrePSystemFixedName_ = ogrePSystemName_ + std::to_string(i);
		i++;
	}

	ogrePSystem_ = MotorCasaPaco::getInstance()->getSM()->createParticleSystem(ogrePSystemFixedName_, ogrePSystemTemplate_);
	ogrePSystem_->setEmitting(false);
	ogrePSystem_->setKeepParticlesInLocalSpace(true);

	e_->getTransform()->getNode()->attachObject(ogrePSystem_);
}

void ParticleSystem::redefine(json& args)
{
}

void ParticleSystem::onActivated()
{
	ogrePSystem_->setEmitting(true);
}

void ParticleSystem::onDeactivated()
{
	ogrePSystem_->setEmitting(false);
}

ParticleSystem::~ParticleSystem()
{
	ogrePSystem_->clear();
	ogrePSystem_->detachFromParent();
	MotorCasaPaco::getInstance()->getSM()->destroyParticleSystem(ogrePSystemFixedName_);
	ogrePSystem_ = nullptr;
}

void ParticleSystem::update()
{
	updateTimeLimit();
}

void ParticleSystem::emit()
{
	timer_ = 0;
	setEnabled(true);
}

void ParticleSystem::updateTimeLimit()
{
	if (timeLimit_ <= 0)
		return;

	if (timer_ < timeLimit_) {
		timer_ += MotorCasaPaco::getInstance()->DeltaTime();
	}
	else {
		if (destroyOnTimeLimit_) e_->getScene()->deleteEntity(e_->getName());
		else ogrePSystem_->setEmitting(false);
	}
}




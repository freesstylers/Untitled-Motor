#include "Light.h"

#include "Core.h"
#include "Transform.h"

Light::Light(json& args) : Component(args)
{
}

Light::~Light()
{
}

void Light::init(json& args)
{

	light = Core::getInstance()->getSM()->createLight(e_->getName() + "_light");

	Ogre::Light::LightTypes lightType = Ogre::Light::LT_POINT;
	Ogre::ColourValue diffuseColour = Ogre::ColourValue(1, 1, 1, 1);
	Ogre::ColourValue specularColour = Ogre::ColourValue(0, 0, 0, 1);
	Ogre::Vector3 lightDir = Ogre::Vector3(0, 0, 0);
	bool castShadows = true;

	float attRange = 100000;
	float attConstant = 1;
	float attLinear = 0;
	float attQuadratic = 0;

	if (!args["lightType"].is_null()) {
		std::string cast = args["lightType"];

		if (cast == "directional")
			lightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;
		else if (cast == "spotlight")
			lightType = Ogre::Light::LightTypes::LT_SPOTLIGHT;
		else
			lightType = Ogre::Light::LightTypes::LT_POINT;
	}

	light->setType(lightType);

	if (!args["diffuseColor"].is_null())
	{
		diffuseColour.r = args["diffuseColor"][0];
		diffuseColour.g = args["diffuseColor"][1];
		diffuseColour.b = args["diffuseColor"][2];
		diffuseColour.a = args["diffuseColor"][3];
	}
	else if (!args["diffuseColour"].is_null())
	{
		diffuseColour.r = args["diffuseColour"][0];
		diffuseColour.g = args["diffuseColour"][1];
		diffuseColour.b = args["diffuseColour"][2];
		diffuseColour.a = args["diffuseColour"][3];
	}

	light->setDiffuseColour(diffuseColour);

	if (!args["specularColor"].is_null())
	{
		specularColour.r = args["specularColor"][0];
		specularColour.g = args["specularColor"][1];
		specularColour.b = args["specularColor"][2];
		specularColour.a = args["specularColor"][3];
	}
	else if (!args["specularColour"].is_null())
	{
		specularColour.r = args["specularColour"][0];
		specularColour.g = args["specularColour"][1];
		specularColour.b = args["specularColour"][2];
		specularColour.a = args["specularColour"][3];
	}

	light->setSpecularColour(specularColour);

	if (lightType == Ogre::Light::LT_SPOTLIGHT) {
		Ogre::Degree spotlightOuterAngle = Ogre::Degree(35);
		Ogre::Degree spotlightInnerAngle = Ogre::Degree(50);
		float spotlightFalloff = 1.0;
		float spotlightNearClip = 1.0;

		if (!args["spotlightNearClip"].is_null())
			spotlightNearClip = args["spotlightNearClip"];
		if (!args["spotlightOuterAngle"].is_null())
			spotlightOuterAngle = args["spotlightOuterAngle"];
		if (!args["spotlightInnerAngle"].is_null())
			spotlightInnerAngle = args["spotlightInnerAngle"];
		if (!args["spotlightFalloff"].is_null())
			spotlightFalloff = args["spotlightFalloff"];

		//OuterAngle is the outer limit of the spotlight (where it fades), InnerAngle is the brightest spot of the spotlight
		//Falloff defines how fast it fades between the inner and outer angle
		//NearClip defines the distance from the spotlight where it ignores any meshes

		light->setSpotlightRange(spotlightInnerAngle, spotlightOuterAngle, spotlightFalloff);
		light->setSpotlightNearClipDistance(spotlightNearClip);
	}

	if (!args["castShadows"].is_null() && args["castShadows"].is_boolean())
		castShadows = args["castShadows"];

	light->setCastShadows(castShadows);


	if (!args["attenuationRange"].is_null())
		attRange = args["attenuationRange"];
	if (!args["attenuationConstant"].is_null())
		attConstant = args["attenuationConstant"];
	if (!args["attenuationLinear"].is_null())
		attLinear = args["attenuationLinear"];
	if (!args["attenuationQuadratic"].is_null())
		attQuadratic = args["attenuationQuadratic"];

	//range is how far the light goes
	//constant is how much it attenuates brightness (0 means no attenuation (AKA too bright), 1 means usual attenuation, higher values mean more attenuation)
	//linear defines how it attenuates brightness linearly
	//quadratic defines how it attenuates brightness quadratically
	//formula: Attenuation = Constant + Linear * Distance + Quadratic * Distance^2


	//if you need more info on the parameters: http://wiki.ogre3d.org/-Point+Light+Attenuation
	light->setAttenuation(attRange, attConstant, attLinear, attQuadratic);


	if (!args["lightDir"].is_null())
	{
		lightDir.x = args["lightDir"][0];
		lightDir.y = args["lightDir"][1];
		lightDir.z = args["lightDir"][2];

		lightDir.normalise();
	}

	light->setDirection(lightDir);

	e_->getComponent<Transform>("Transform")->getNode()->attachObject(light);
}

void Light::redefine(json& args)
{

	Ogre::Light::LightTypes lightType = light->getType();

	if (!args["lightType"].is_null()) {
		std::string cast = args["lightType"];

		if (cast == "directional")
			lightType = Ogre::Light::LightTypes::LT_DIRECTIONAL;
		else if (cast == "spotlight")
			lightType = Ogre::Light::LightTypes::LT_SPOTLIGHT;
		else
			lightType = Ogre::Light::LightTypes::LT_POINT;

		light->setType(lightType);
	}


	if (lightType == Ogre::Light::LT_SPOTLIGHT) {
		Ogre::Degree spotlightOuterAngle = Ogre::Degree(35);
		Ogre::Degree spotlightInnerAngle = Ogre::Degree(50);
		float spotlightFalloff = 1.0;
		float spotlightNearClip = 1.0;

		if (!args["spotlightNearClip"].is_null())
			spotlightNearClip = args["spotlightNearClip"];
		if (!args["spotlightOuterAngle"].is_null())
			spotlightOuterAngle = args["spotlightOuterAngle"];
		if (!args["spotlightInnerAngle"].is_null())
			spotlightInnerAngle = args["spotlightInnerAngle"];
		if (!args["spotlightFalloff"].is_null())
			spotlightFalloff = args["spotlightFalloff"];


		light->setSpotlightRange(spotlightInnerAngle, spotlightOuterAngle, spotlightFalloff);
		light->setSpotlightNearClipDistance(spotlightNearClip);
	}


	if (!args["lightDir"].is_null())
	{
		Ogre::Vector3 lightDir = Ogre::Vector3(0, 0, 0);

		lightDir.x = args["lightDir"][0];
		lightDir.y = args["lightDir"][1];
		lightDir.z = args["lightDir"][2];

		lightDir.normalise();

		light->setDirection(lightDir);
	}


	Ogre::Vector4 att = light->getAttenuation();
	float attRange = att.x;
	float attConstant = att.y;
	float attLinear = att.z;
	float attQuadratic = att.w;

	if (!args["attenuationRange"].is_null())
		attRange = args["attenuationRange"];
	if (!args["attenuationConstant"].is_null())
		attConstant = args["attenuationConstant"];
	if (!args["attenuationLinear"].is_null())
		attLinear = args["attenuationLinear"];
	if (!args["attenuationQuadratic"].is_null())
		attQuadratic = args["attenuationQuadratic"];

	light->setAttenuation(attRange, attConstant, attLinear, attQuadratic);


	if (!args["castShadows"].is_null() && args["castShadows"].is_boolean())
		light->setCastShadows(args["castShadows"]);

	if (!args["diffuseColor"].is_null())
	{
		Ogre::ColourValue diffuseColour = Ogre::ColourValue(1, 1, 1, 1);
		diffuseColour.r = args["diffuseColor"][0];
		diffuseColour.g = args["diffuseColor"][1];
		diffuseColour.b = args["diffuseColor"][2];
		diffuseColour.a = args["diffuseColor"][3];

		light->setDiffuseColour(diffuseColour);
	}
	else if (!args["diffuseColour"].is_null())
	{
		Ogre::ColourValue diffuseColour = Ogre::ColourValue(1, 1, 1, 1);
		diffuseColour.r = args["diffuseColour"][0];
		diffuseColour.g = args["diffuseColour"][1];
		diffuseColour.b = args["diffuseColour"][2];
		diffuseColour.a = args["diffuseColour"][3];

		light->setDiffuseColour(diffuseColour);
	}

	if (!args["specularColor"].is_null())
	{
		Ogre::ColourValue specularColour = Ogre::ColourValue(1, 1, 1, 1);
		specularColour.r = args["specularColor"][0];
		specularColour.g = args["specularColor"][1];
		specularColour.b = args["specularColor"][2];
		specularColour.a = args["specularColor"][3];

		light->setSpecularColour(specularColour);
	}
	else if (!args["specularColour"].is_null())
	{
		Ogre::ColourValue specularColour = Ogre::ColourValue(1, 1, 1, 1);
		specularColour.r = args["specularColour"][0];
		specularColour.g = args["specularColour"][1];
		specularColour.b = args["specularColour"][2];
		specularColour.a = args["specularColour"][3];

		light->setSpecularColour(specularColour);
	}
}

#include <Ogre.h>

#include "Scene/Skybox.h"
#include "MotorCasaPaco.h"

Skybox::Skybox(json& args) : Component(args)
{
}

Skybox::~Skybox()
{
}

void Skybox::init(json& args)
{
	skyType = SkyType::DOME;
	material = "blank";
	distance = 5000;
	drawFirst = false;


	if (!args["skyType"].is_null()) {
		std::string cast = args["skyType"];

		if (cast == "plane")	skyType = SkyType::PLANE;
		else if (cast == "box")	skyType = SkyType::BOX;
		else	skyType = SkyType::DOME;
	}

	if (!args["material"].is_null()) {
		std::string cast = args["material"];
		material = cast;
	}

	if (!args["distance"].is_null()) distance = args["distance"];

	if (!args["drawFirst"].is_null() && args["drawFirst"].is_boolean())	drawFirst = args["drawFirst"];

	if (skyType == DOME) {
		curvature = 10;
		tiling = 8;

		if (!args["tiling"].is_null()) tiling = args["tiling"];
		if (!args["curvature"].is_null()) curvature = args["curvature"];
	}
	else if (skyType == PLANE) {
		scale = 1000;
		tiling = 10;
		bow = 0;
		xSegments = 1;
		ySegments = 1;

		normal = Ogre::Vector3::NEGATIVE_UNIT_Y;

		if (!args["tiling"].is_null()) tiling = args["tiling"];
		if (!args["scale"].is_null()) scale = args["scale"];
		if (!args["bow"].is_null()) bow = args["bow"];
		if (!args["xSegments"].is_null()) xSegments = args["xSegments"];
		if (!args["ySegments"].is_null()) ySegments = args["ySegments"];

		if (!args["normal"].is_null())
		{
			std::string cast = args["normal"];

			if (cast == "x")	normal = Ogre::Vector3::UNIT_X;
			else if (cast == "-x")	normal = Ogre::Vector3::NEGATIVE_UNIT_X;
			else if (cast == "z")	normal = Ogre::Vector3::UNIT_Z;
			else if (cast == "-z")	normal = Ogre::Vector3::NEGATIVE_UNIT_Z;
			else if (cast == "y")	normal = Ogre::Vector3::UNIT_Y;
			else	normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
		}
	}

	makeSky();
}

void Skybox::redefine(json& args)
{
	setEnabled(false);


	if (!args["skyType"].is_null()) {
		std::string cast = args["skyType"];

		if (cast == "plane")	skyType = SkyType::PLANE;
		else if (cast == "box")	skyType = SkyType::BOX;
		else	skyType = SkyType::DOME;
	}

	if (!args["material"].is_null()) {
		std::string cast = args["material"];
		material = cast;
	}

	if (!args["distance"].is_null()) distance = args["distance"];

	if (!args["drawFirst"].is_null() && args["drawFirst"].is_boolean())	drawFirst = args["drawFirst"];

	if (skyType == DOME) {
		if (!args["tiling"].is_null()) tiling = args["tiling"];
		if (!args["curvature"].is_null()) curvature = args["curvature"];
	}
	else if (skyType == PLANE) {
		if (!args["tiling"].is_null()) tiling = args["tiling"];
		if (!args["scale"].is_null()) scale = args["scale"];
		if (!args["bow"].is_null()) bow = args["bow"];
		if (!args["xSegments"].is_null()) xSegments = args["xSegments"];
		if (!args["ySegments"].is_null()) ySegments = args["ySegments"];

		if (!args["normal"].is_null())
		{
			std::string cast = args["normal"];

			if (cast == "x")	normal = Ogre::Vector3::UNIT_X;
			else if (cast == "-x")	normal = Ogre::Vector3::NEGATIVE_UNIT_X;
			else if (cast == "z")	normal = Ogre::Vector3::UNIT_Z;
			else if (cast == "-z")	normal = Ogre::Vector3::NEGATIVE_UNIT_Z;
			else if (cast == "y")	normal = Ogre::Vector3::UNIT_Y;
			else	normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
		}
	}

	makeSky();
}

void Skybox::setEnabled(bool b)
{
	Ogre::SceneManager* sm = MotorCasaPaco::getInstance()->getSM();

	switch (skyType) {
	case PLANE:
		sm->setSkyPlaneEnabled(b);
		break;
	case DOME:
		sm->setSkyDomeEnabled(b);
		break;
	case BOX:
	default:
		sm->setSkyBoxEnabled(b);
		break;
	}
}

void Skybox::makeSky()
{
	Ogre::SceneManager* sm = MotorCasaPaco::getInstance()->getSM();

	switch (skyType) {
		case PLANE:
			plane.d = distance;
			plane.normal = normal;
			sm->setSkyPlane(true, plane, material, scale, tiling, drawFirst, bow, xSegments, ySegments);
			break;
		case DOME:
			sm->setSkyDome(true, material, curvature, tiling, distance, drawFirst);
			break;
		case BOX:
		default:
			sm->setSkyBox(true, material, distance, drawFirst);
			break;
	}
}

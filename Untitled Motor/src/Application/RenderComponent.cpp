#include "RenderComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(std::string tag, Ogre::SceneManager* sM, std::string mesh, std::string material, Ogre::SceneNode* father) :Component(tag)
{
	sceneManager = sM;
	if (father != nullptr)
		node = father->createChildSceneNode();
	else
		node = sceneManager->getRootSceneNode()->createChildSceneNode();
	ent = sM->createEntity(mesh);
	if(material!="")
		ent->setMaterialName(material);
	node->attachObject(ent);
}

void RenderComponent::update()
{
	TransformComponent* trans=getEntity()->getComponent<TransformComponent>("transform");
	node->setPosition(trans->getPosition());
	node->setOrientation(trans->getRotation());
	node->setScale(trans->getScale());
}

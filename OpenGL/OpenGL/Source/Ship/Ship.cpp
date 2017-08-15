#include "stdafx.h"

#include "Ship/Ship.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Rendering/SpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "DataConverters/ShipDataConverter.h"
#include "DataConverters/AnimationDataConverter.h"
#include "Animation/StateMachine.h"
#include "Screens/Screen.h"
#include "Turrets/Turret.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Ship::create(const Handle<GameObject>& gameObject)
  {
    ShipDataConverter loader(getResourceManager()->load<Data>(Path("Ships", "Fiirkan.xml")).as_const());

    const Handle<Rendering::SpriteRenderer>& renderer = SpriteRenderer::create(gameObject, loader.getTextureRelativePath());

    const Handle<RigidBody2D>& shipRigidBody = RigidBody2D::create(gameObject, glm::vec2(), 0);
    shipRigidBody->setMaxLinearVelocity(glm::vec2(loader.getLinearSpeed()));
    shipRigidBody->setMaxAngularVelocity(loader.getAngularSpeed());
    const Handle<Input::KeyboardRigidBody2DController>& movementController = gameObject->addComponent<Input::KeyboardRigidBody2DController>();
      
    AnimationDataConverter animationLoader(getResourceManager()->load<Data>(Path("Turrets", "ChainBlaster.xml")).as_const());

    const Handle<GameObject>& turret = gameObject->allocateGameObjectInSameLayer(gameObject->getTransform());
    const Handle<Turret>& turretController = turret->addComponent<Turret>();
    const Handle<SpriteRenderer>& turretRenderer = turret->addComponent<SpriteRenderer>();
    const Handle<Animation>& animation = Animation::create(
      turret, 
      "Firing", 
      animationLoader.getSecondsPerFrame(),
      Animation::LoopMode::kLooping,
      animationLoader.getFrames());
  }
}
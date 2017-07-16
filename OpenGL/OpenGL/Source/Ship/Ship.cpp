#include "stdafx.h"

#include "Ship/Ship.h"
#include "Input/KeyboardRigidBody2DController.h"
#include "Rendering/SpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "DataConverters/ShipDataConverter.h"
#include "DataConverters/AnimationDataConverter.h"
#include "Animation/StateMachine.h"
#include "Screens/Screen.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Ship::create(const Handle<GameObject>& gameObject)
  {
    ShipDataConverter loader(getResourceManager()->loadData(Path("Ships", "Fiirkan.xml")).as_const());

    const Handle<Rendering::SpriteRenderer>& renderer = gameObject->addComponent<Rendering::SpriteRenderer>();
    renderer->setTexture(loader.getTextureRelativePath());

    gameObject->addComponent<Input::KeyboardRigidBody2DController>();

    AnimationDataConverter animationLoader(getResourceManager()->loadData(Path("Turrets", "ChainBlaster.xml")).as_const());

    const Handle<GameObject>& turret = gameObject->getOwnerScreen()->createGameObject(gameObject->getTransform());
    const Handle<SpriteRenderer>& turretRenderer = turret->addComponent<SpriteRenderer>();
    const Handle<Animation>& animation = Animation::create(
      turret, 
      "Firing", 
      animationLoader.getSecondsPerFrame(),
      Animation::LoopMode::kLooping,
      animationLoader.getFrames());
  }
}
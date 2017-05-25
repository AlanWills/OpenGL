#include "stdafx.h"

#include "Ship/Ship.h"
#include "Ship/KeyboardShipController.h"
#include "Rendering/SpriteRenderer.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Ship::create(const Handle<GameObject>& gameObject)
  {
    const Handle<Rendering::SpriteRenderer>& renderer = gameObject->addComponent<Rendering::SpriteRenderer>();
    renderer->setTexture("Fiirkan.png");

    gameObject->addComponent<KeyboardShipController>();
  }
}
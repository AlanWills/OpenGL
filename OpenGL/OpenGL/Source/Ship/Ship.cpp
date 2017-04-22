#include "stdafx.h"

#include "Ship/Ship.h"
#include "Ship/KeyboardShipController.h"
#include "Rendering/SpriteRenderer.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Ship::createShip(const Handle<GameObject>& gameObject)
  {
    const Handle<SpriteRenderer>& renderer = gameObject->addComponent(SpriteRenderer::allocate());
    renderer->setTexture("Fiirkan.png");

    gameObject->addComponent(KeyboardShipController::allocate());
  }
}
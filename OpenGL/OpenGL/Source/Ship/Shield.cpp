#include "stdafx.h"

#include "Ship/Shield.h"
#include "Rendering/SpriteRenderer.h"
#include "GraphicalFX/OpacityLerper.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Shield::create(const Handle<GameObject>& shield)
  {
    const Handle<Rendering::SpriteRenderer>& spriteRenderer = shield->addComponent<Rendering::SpriteRenderer>();
    spriteRenderer->setTexture("EnergyShield.png");
    spriteRenderer->setColour(0, 0, 1, 0.25f);

    const Handle<OpacityLerper>& lerper = shield->addComponent<OpacityLerper>();
  }
}
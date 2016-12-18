#include "stdafx.h"

#include "Screens/Screen.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Screen::Screen()
  {
  }

  //------------------------------------------------------------------------------------------------
  Screen::~Screen()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Screen::initialize()
  {
    GameObject* gameObject = m_gameObjects.allocate();
    SpriteRenderer* spriteRenderer = GameManager::getRenderManager()->constructAndInitializeRenderer();
    gameObject->addComponent(spriteRenderer);

    spriteRenderer->setTexture(internString("container.jpg"));
  }
}
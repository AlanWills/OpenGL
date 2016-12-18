#include "stdafx.h"

#include "Screens/Screen.h"
#include "Game/GameManager.h"
#include "Scripts/ScriptManager.h"


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
    Inherited::initialize();

    GameObject* gameObject = m_gameObjects.allocateAndInitialize();
    SpriteRenderer* spriteRenderer = GameManager::getRenderManager()->allocateAndInitializeRenderer();
    spriteRenderer->setTexture(internString("container.jpg"));
    gameObject->addComponent(spriteRenderer);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_gameObjects.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_gameObjects.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::render(GLfloat lag)
  {
    Inherited::render(lag);

    m_gameObjects.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::die()
  {
    Inherited::die();

    m_gameObjects.die();
  }
}
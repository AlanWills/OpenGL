#include "stdafx.h"

#include "Screens/Screen.h"
#include "Game/GameManager.h"
#include "Scripts/ScriptManager.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{
  REGISTER_COMPONENT(Screen);

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

    m_gameObjects.allocateAndInitialize()->addComponent(SpriteRenderer::allocateAndInitialize())->setTexture("container");
    m_gameObjects.allocateAndInitialize()->addComponent(SpriteRenderer::allocateAndInitialize())->setTexture("awesomeface");
  }

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_gameObjects.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::awake()
  {
    Inherited::awake();

    m_gameObjects.awake();
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
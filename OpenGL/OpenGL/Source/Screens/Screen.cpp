#include "stdafx.h"

#include "Screens/Screen.h"
#include "Game/GameManager.h"


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
  void Screen::initialize(const Handle<Component>& allocHandle)
  {
    Inherited::initialize(allocHandle);

    m_renderManager.initialize(getAllocatorHandle());
    m_uiManager.initialize(getAllocatorHandle());
  }

  //------------------------------------------------------------------------------------------------
  void Screen::awake()
  {
    Inherited::awake();

    m_renderManager.awake();
    m_gameObjects.awake();
    m_uiManager.awake();
  }

  //------------------------------------------------------------------------------------------------
  void Screen::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_renderManager.handleInput(elapsedGameTime);
    m_gameObjects.handleInput(elapsedGameTime);
    m_uiManager.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_renderManager.update(secondsPerUpdate);
    m_gameObjects.update(secondsPerUpdate);
    m_uiManager.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::render(GLfloat lag)
  {
    Inherited::render(lag);

    m_renderManager.render(lag);
    m_gameObjects.render(lag);
    m_uiManager.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void Screen::die()
  {
    Inherited::die();

    m_renderManager.die();
    m_gameObjects.die();
    m_uiManager.die();
  }
}
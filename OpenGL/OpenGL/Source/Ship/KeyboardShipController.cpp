#include "stdafx.h"

#include "Ship/KeyboardShipController.h"
#include "Input/InputManager.h"


namespace SpaceGame
{
  REGISTER_COMPONENT(KeyboardShipController)

  //------------------------------------------------------------------------------------------------
  KeyboardShipController::KeyboardShipController() :
    m_moveForwardKey(GLFW_KEY_UP),
    m_moveBackwardKey(GLFW_KEY_DOWN)
  {
  }

  //------------------------------------------------------------------------------------------------
  KeyboardShipController::~KeyboardShipController()
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardShipController::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    const Handle<Keyboard>& keyboard = getKeyboard();
    if (keyboard->isKeyDown(m_moveForwardKey))
    {
      getParent()->getTransform()->translate(0, 100 * elapsedGameTime);
    }

    if (keyboard->isKeyDown(m_moveBackwardKey))
    {
      getParent()->getTransform()->translate(0, -100 * elapsedGameTime);
    }
  }
}
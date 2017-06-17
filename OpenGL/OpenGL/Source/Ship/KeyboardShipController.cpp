#include "stdafx.h"

#include "Ship/KeyboardShipController.h"
#include "Input/InputManager.h"


namespace SpaceGame
{
  using namespace Input;

  REGISTER(KeyboardShipController)

  //------------------------------------------------------------------------------------------------
  KeyboardShipController::KeyboardShipController() :
    m_linearSpeed(300),
    m_angularSpeed(1),
    m_moveForwardKey(GLFW_KEY_UP),
    m_moveBackwardKey(GLFW_KEY_DOWN),
    m_rotateLeftKey(GLFW_KEY_LEFT),
    m_rotateRightKey(GLFW_KEY_RIGHT)
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
    const Handle<Transform>& transform = getTransform();

    if (keyboard->isKeyDown(m_moveForwardKey))
    {
      transform->translate(glm::vec3(transform->getLocalMatrix()[1] * m_linearSpeed * elapsedGameTime));
    }

    if (keyboard->isKeyDown(m_moveBackwardKey))
    {
      transform->translate(glm::vec3(-transform->getLocalMatrix()[1] * m_linearSpeed * elapsedGameTime));
    }

    if (keyboard->isKeyDown(m_rotateLeftKey))
    {
      transform->rotate(m_angularSpeed * elapsedGameTime);
    }

    if (keyboard->isKeyDown(m_rotateRightKey))
    {
      transform->rotate(-m_angularSpeed * elapsedGameTime);
    }
  }
}
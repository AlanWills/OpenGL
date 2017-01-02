#include "stdafx.h"

#include "Input/KeyboardMovementScript.h"
#include "Scripts/ScriptManager.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(KeyboardMovementScript)

  //------------------------------------------------------------------------------------------------
  KeyboardMovementScript::KeyboardMovementScript() :
    m_transform(nullptr),
    m_moveLeftKey(GLFW_KEY_A),
    m_moveRightKey(GLFW_KEY_D),
    m_moveUpKey(GLFW_KEY_W),
    m_moveDownKey(GLFW_KEY_S),
    m_panSpeed(1)
  {
  }

  //------------------------------------------------------------------------------------------------
  KeyboardMovementScript::~KeyboardMovementScript()
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardMovementScript::awake()
  {
    Inherited::awake();

    ASSERT(getParent().get());
    m_transform = &getParent()->getTransform();
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardMovementScript::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    if (m_transform)
    {
      // Zero the direction again
      m_directionVector = glm::vec3();

      Keyboard* keyboard = GameManager::getInputManager()->getKeyboard();

      const glm::mat4& localMat = m_transform->getLocalMatrix();

      // Only support one left/right key pressed
      if (keyboard->isKeyDown(m_moveRightKey))
      {
        // Move along +ve local space x axis (right in local space)
        m_directionVector += glm::vec3(localMat[0]);
      }
      else if (keyboard->isKeyDown(m_moveLeftKey))
      {
        // Move along -ve local space x axis (left in local space)
        m_directionVector -= glm::vec3(localMat[0]);
      }

      if (keyboard->isKeyDown(m_moveUpKey))
      {
        // Move along +ve local space y axis (up in local space)
        m_directionVector += glm::vec3(localMat[1]);
      }
      else if (keyboard->isKeyDown(m_moveDownKey))
      {
        // Move along -+ve local space y axis (down in local space)
        m_directionVector -= glm::vec3(localMat[1]);
      }

      if (m_directionVector != glm::vec3())
      {
        // Normalize the direction vector
        //m_directionVector /= length;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardMovementScript::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    if (m_transform && (m_directionVector != glm::vec3()))
    {
      m_transform->translate(m_directionVector * m_panSpeed * secondsPerUpdate);
    }
  }
}
#include "stdafx.h"

#include "Viewport/Camera.h"
#include "Game/GameManager.h"
#include "Scripts/ScriptManager.h"
#include "Scripts/KeyboardMovementScript.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookDirection, glm::vec3 upDirection)
  {
    m_transform.setLocalMatrix(glm::lookAt(cameraPosition, cameraPosition + lookDirection, upDirection));
  }

  //------------------------------------------------------------------------------------------------
  Camera::~Camera()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Camera::initialize()
  {
    Inherited::initialize();

    if (KeyboardMovementScript::canAllocate())
    {
      KeyboardMovementScript* keyboardMovementScript = addComponent(KeyboardMovementScript::allocateAndInitialize());
      keyboardMovementScript->setTransform(&m_transform);
      keyboardMovementScript->setMoveUpKey(GLFW_KEY_S);
      keyboardMovementScript->setMoveDownKey(GLFW_KEY_W);
    }
    else
    {
      ASSERT_FAIL();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Camera::pan(const glm::vec3& translation)
  {
    m_transform.translate(translation);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getProjectionMatrix() const
  {
    return glm::perspective<float>(45.0f, 1, 0.1f, 100);
  }

  //------------------------------------------------------------------------------------------------
  const glm::mat4& Camera::getViewMatrix() const
  {
    // Maybe expand this later, but for now it's going to be a top down camera
    return m_transform.getLocalMatrix();
  }
}
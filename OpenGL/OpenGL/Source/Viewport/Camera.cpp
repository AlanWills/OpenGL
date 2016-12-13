#include "stdafx.h"

#include "Viewport/Camera.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookDirection, glm::vec3 upDirection) :
    m_transform(glm::lookAt(cameraPosition, cameraPosition + lookDirection, upDirection)),
    m_panSpeed(1)
  {
  }

  //------------------------------------------------------------------------------------------------
  Camera::~Camera()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Camera::handleInput(GLfloat elapsedGameTime)
  {
    Keyboard* keyboard = GameManager::getInputManager()->getKeyboard();

    const glm::mat4& localMat = m_transform.getLocalMatrix();

    // Only support one left/right key pressed
    if (keyboard->isKeyDown(GLFW_KEY_A))
    {
      // Move along +ve local space x axis (right in local space)
      pan(glm::vec3(localMat[0]) * m_panSpeed * elapsedGameTime);
    }
    else if (keyboard->isKeyDown(GLFW_KEY_D))
    {
      // Move along -ve local space x axis (left in local space)
      pan(glm::vec3(localMat[0]) * -m_panSpeed * elapsedGameTime);
    }

    if (keyboard->isKeyDown(GLFW_KEY_W))
    {
      // Move along +ve local space y axis (up in local space)
      pan(glm::vec3(localMat[1]) * m_panSpeed * elapsedGameTime);
    }
    else if (keyboard->isKeyDown(GLFW_KEY_S))
    {
      // Move along -+ve local space y axis (down in local space)
      pan(glm::vec3(localMat[1]) * -m_panSpeed * elapsedGameTime);
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
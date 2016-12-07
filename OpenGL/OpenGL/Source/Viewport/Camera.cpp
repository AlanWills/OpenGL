#include "stdafx.h"

#include "Viewport/Camera.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Camera::Camera()
  {

  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getProjectionMatrix()
  {
    return glm::perspective<float>(45.0f, 1, 0.1f, 100);
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Camera::getViewMatrix()
  {
    return glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  }
}
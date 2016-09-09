#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

//------------------------------------------------------------------------------------------------
Camera::Camera()
: m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
  m_lookDirection(glm::vec3(0.0f, 0.0f, -1.0f)),
  m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
  m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
  m_yaw(-90.0f),
  m_pitch(0.0f),
  m_zoom(45.0f),
  m_speed(5.0f),
  m_sensitivity(0.05f),
  m_near(0.1f),
  m_far(100),
  m_firstMouse(true)
{
  updateCameraVectors();
}

//------------------------------------------------------------------------------------------------
void Camera::getViewMatrix(glm::mat4& outputView) const
{
  outputView = glm::lookAt(m_cameraPos, m_cameraPos + m_lookDirection, m_up);
}

//------------------------------------------------------------------------------------------------
void Camera::getProjectionMatrix(GLuint viewportWidth, GLuint viewportHeight, glm::mat4& outputProj) const
{
  outputProj = glm::perspective(glm::radians(m_zoom), (float)viewportWidth / (float)viewportHeight, 0.1f, 100.0f);
}

//------------------------------------------------------------------------------------------------
void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset)
{
  xOffset *= m_sensitivity;
  yOffset *= m_sensitivity;

  m_yaw += xOffset;
  m_pitch += yOffset;

  m_yaw = glm::mod(m_yaw, 360.0f);
  m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);

  updateCameraVectors();
}

//------------------------------------------------------------------------------------------------
void Camera::zoom(GLfloat zoomDelta)
{
  m_zoom = glm::clamp(m_zoom - zoomDelta, 1.0f, 45.0f);
}

//------------------------------------------------------------------------------------------------
void Camera::move(CameraMovement cameraMovement, GLfloat deltaTime)
{
  GLfloat velocity = m_speed * deltaTime;

  if (cameraMovement == kForward)
  {
    m_cameraPos += m_lookDirection * velocity;
  }
  if (cameraMovement == kBackward)
  {
    m_cameraPos -= m_lookDirection * velocity;
  }
  if (cameraMovement == kLeft)
  {
    m_cameraPos -= m_right * velocity;
  }
  if (cameraMovement == kRight)
  {
    m_cameraPos += m_right * velocity;
  }
}

//------------------------------------------------------------------------------------------------
void Camera::updateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
  front.y = sin(glm::radians(m_pitch));
  front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

  assert(glm::length(m_worldUp) == 1.0f);

  // By assuming the m_worldUp vector is a normal vector, we can use the fact that
  // the cross product does not change lengths to avoid normalizing the m_right & m_up vectors
  m_lookDirection = glm::normalize(front);
  m_right = glm::cross(m_lookDirection, m_worldUp);
  m_up = glm::cross(m_right, m_lookDirection);
}
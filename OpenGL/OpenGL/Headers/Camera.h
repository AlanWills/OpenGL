#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

enum CameraMovement
{
  kForward,
  kBackward,
  kLeft,
  kRight,
};

class Camera
{

public:
  static Camera& getInstance();

  void getViewMatrix(glm::mat4& outputView) const;
  void getProjectionMatrix(GLuint viewportWidth, GLuint viewportHeight, glm::mat4& outputProj) const;

  void processMouseMovement(GLfloat xOffset, GLfloat yOffset);
  void move(CameraMovement cameraMovement, GLfloat deltaTime);
  void zoom(GLfloat zoomDelta);

private:
  Camera();

  void updateCameraVectors();

  glm::vec3 m_cameraPos;
  glm::vec3 m_lookDirection;
  glm::vec3 m_right;
  glm::vec3 m_up;
  glm::vec3 m_worldUp;

  GLfloat m_pitch;
  GLfloat m_yaw;
  GLfloat m_zoom;
  GLfloat m_speed;
  GLfloat m_sensitivity;
  GLfloat m_near;
  GLfloat m_far;

  bool m_firstMouse;
};
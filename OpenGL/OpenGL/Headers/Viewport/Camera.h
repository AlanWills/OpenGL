#pragma once

#include "GLHeaders.h"
#include "Maths/Transform.h"


namespace OpenGL
{

class Camera
{
  public:
    Camera(glm::vec3 cameraPosition, glm::vec3 lookDirection, glm::vec3 upDirection = glm::vec3(0, 1, 0));
    ~Camera();

    void handleInput(GLfloat elapsedGameTime);

    /// \brief Performs a translation of the camera's position by the inputted translation vector
    void pan(const glm::vec3& translation); 

    glm::mat4 getProjectionMatrix() const;
    const glm::mat4& getViewMatrix() const;

  protected:
    Transform m_transform;

    float m_panSpeed;
};

}
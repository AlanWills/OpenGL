#pragma once

#include "OpenGL/GLHeaders.h"
#include "Objects/GameObject.h"


namespace OpenGL
{

class Camera : public GameObject
{
  public:
    Camera(float aspectRatio, 
           float nearPlane, 
           float farPlane, 
           glm::vec3 cameraPosition, 
           glm::vec3 lookDirection, 
           glm::vec3 upDirection = glm::vec3(0, 1, 0));
    ~Camera();

    void initialize();

    /// \brief Performs a translation of the camera's position by the inputted translation vector
    void pan(const glm::vec3& translation); 

    glm::mat4 getPerspectiveProjectionMatrix() const;
    glm::mat4 getOrthographicProjectionMatrix() const;
    const glm::mat4& getViewMatrix() const;

  private:
    typedef GameObject Inherited;

    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
};

}
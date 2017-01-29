#pragma once

#include "OpenGL/GLHeaders.h"
#include "Objects/GameObject.h"
#include "Maths/Ray.h"


namespace OpenGL
{

class Camera : public GameObject
{
  public:
    Camera();
    ~Camera();

    void initialize(Handle<Component> allocHandle);

    /// \brief Performs a translation of the camera's position by the inputted translation vector
    void pan(const glm::vec3& translation); 

    glm::mat4 getPerspectiveProjectionMatrix() const;
    glm::mat4 getOrthographicProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

    /// \brief Create a ray from the camera's eye to the position in world space that is unprojected from the inputted screen position
    Ray createRay(const glm::vec2& screenPosition) const;

    void setAspectRatio(float aspectRatio);

  private:
    typedef GameObject Inherited;

    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
};

}
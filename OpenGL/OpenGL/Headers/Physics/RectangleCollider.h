#pragma once

#include "Collider.h"


namespace OpenGL
{

class RectangleCollider : public Collider
{
  DECLARE_COMPONENT_WITH_MANAGER(RectangleCollider, 10, InputManager);

  public:
    void render(GLfloat lag) override;

    bool intersectsRay(const Ray& ray) const override;
    bool intersectsPoint(const glm::vec2& point) const override;

    void setDimensions(glm::vec2& dimensions) { m_dimensions = dimensions; }

  private:
    typedef Component Inherited;

    glm::vec2 m_dimensions;
};

}
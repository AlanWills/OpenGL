#pragma once

#include "Collider.h"


namespace OpenGL
{

class RectangleCollider : public Collider
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, RectangleCollider, 10, InputManager);

  public:
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

    bool intersects(const Ray& ray) const override;
    bool intersects(const glm::vec2& point) const override { return m_rectangle.contains(point); }
    bool intersects(const Rectangle& rectangle) const override { return m_rectangle.intersects(rectangle); }

    const glm::vec2& getDimensions() const { return m_rectangle.dimensions(); }
    void setDimensions(const glm::vec2& dimensions) { m_rectangle.set_dimensions(dimensions); }

    float left() const { return m_rectangle.left(); }
    float top() const { return m_rectangle.top(); }
    float right() const { return m_rectangle.right(); }
    float bottom() const { return m_rectangle.bottom(); }
    float width() const { return m_rectangle.dimensions().x; }
    float height() const { return m_rectangle.dimensions().y; }

  private:
    typedef Component Inherited;

    Rectangle m_rectangle;
};

}
#pragma once

#include "OpenGL/GLHeaders.h"


namespace OpenGL
{

class Rectangle
{
  public:
    Rectangle();
    Rectangle(const glm::vec2& centre, const glm::vec2& dimensions);

    const glm::vec2& centre() const { return m_centre; }
    const glm::vec2& dimensions() const { return m_dimensions; }
    float left() const { return m_centre.x - m_dimensions.x * 0.5f; }
    float top() const { return m_centre.y + m_dimensions.y * 0.5f; }
    float right() const { return m_centre.x + m_dimensions.x * 0.5f; }
    float bottom() const { return m_centre.y - m_dimensions.y * 0.5f; }

    void set_centre(const glm::vec2& centre) { m_centre = centre; }
    void set_dimensions(const glm::vec2& dimensions) { m_dimensions = dimensions; }

    bool contains(const glm::vec2& point) const;
    bool intersects(const Rectangle& point) const;

  private:
    glm::vec2 m_centre;
    glm::vec2 m_dimensions;
};

}
#include "stdafx.h"

#include "Maths/Rectangle.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Rectangle::Rectangle() : 
    m_centre(0, 0), 
    m_dimensions(0, 0)
  {
  }

  //------------------------------------------------------------------------------------------------
  Rectangle::Rectangle(const glm::vec2& centre, const glm::vec2& dimensions) : 
    m_centre(centre), 
    m_dimensions(dimensions) 
  {
  }

  //------------------------------------------------------------------------------------------------
  bool Rectangle::contains(const glm::vec2& point) const
  {
    glm::vec2 halfDims = m_dimensions * 0.5f;

    return ((m_centre.x - halfDims.x) <= point.x) &&
           ((m_centre.x + halfDims.x) >= point.x) &&
           ((m_centre.y) <= point.y) &&
           ((m_centre.y) + m_dimensions.y >= point.y);
  }

  //------------------------------------------------------------------------------------------------
  bool Rectangle::intersects(const Rectangle& rectangle) const
  {
    return left() < rectangle.right() &&
           right() > rectangle.left() &&
           top() < rectangle.bottom() &&
           bottom() > rectangle.top();
  }
}
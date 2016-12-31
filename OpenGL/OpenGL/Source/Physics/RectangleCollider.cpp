#include "stdafx.h"

#include "Physics/RectangleCollider.h"


namespace OpenGL
{
  REGISTER_COMPONENT(RectangleCollider)

  //------------------------------------------------------------------------------------------------
  RectangleCollider::RectangleCollider() :
    m_dimensions(glm::vec2())
  {
  }

  //------------------------------------------------------------------------------------------------
  RectangleCollider::~RectangleCollider()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::render(GLfloat lag)
  {
    Inherited::render(lag);

    //ASSERT_FAIL_MSG("TODO - debug rendering");
  }

  //------------------------------------------------------------------------------------------------
  bool RectangleCollider::intersectsRay(const Ray& ray) const
  {
    if (!m_transform)
    {
      ASSERT_FAIL();
      return false;
    }

    // Calculate the point of intersection in the z plane our transform is on
    // For now we are assuming all textures are perpendicular to z
    // We also do not handle rotation at the moment (should be ok - just rotate the dims vector
    // Why is the y like this, bleurgh
    glm::vec3 translation = m_transform->getTranslation();

    float t = (translation.z - ray.m_origin.z) / ray.m_direction.z;
    glm::vec2 intersectPoint(ray.m_origin.x + t * ray.m_direction.x, ray.m_origin.y + t * ray.m_direction.y);

    return intersectsPoint(intersectPoint);
  }

  //------------------------------------------------------------------------------------------------
  bool RectangleCollider::intersectsPoint(const glm::vec2& point) const
  {
    if (!m_transform)
    {
      ASSERT_FAIL();
      return false;
    }

    glm::vec3 translation = m_transform->getTranslation();
    glm::vec2 halfDims = m_dimensions * 0.5f;

    return ((translation.x - halfDims.x) <= point.x) &&
           ((translation.x + halfDims.x) >= point.x) &&
           ((translation.y) <= point.y) &&
           ((translation.y) + m_dimensions.y>= point.y);
  }
}
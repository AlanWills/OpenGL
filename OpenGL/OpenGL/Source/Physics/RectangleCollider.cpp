#include "stdafx.h"

#include "Physics/RectangleCollider.h"


namespace OpenGL
{
  REGISTER_COMPONENT(RectangleCollider)

  //------------------------------------------------------------------------------------------------
  RectangleCollider::RectangleCollider() :
    m_rectangle()
  {
  }

  //------------------------------------------------------------------------------------------------
  RectangleCollider::~RectangleCollider()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    ASSERT(m_transform.get());
    const glm::vec3& worldTrans = m_transform->getWorldTranslation();
    m_rectangle.set_centre(glm::vec2(worldTrans.x, worldTrans.y));
  }

  //------------------------------------------------------------------------------------------------
  void RectangleCollider::render(GLfloat lag)
  {
    Inherited::render(lag);

    //ASSERT_FAIL_MSG("TODO - debug rendering");
  }

  //------------------------------------------------------------------------------------------------
  bool RectangleCollider::intersects(const Ray& ray) const
  {
    if (!m_transform.get())
    {
      ASSERT_FAIL();
      return false;
    }

    // Calculate the point of intersection in the z plane our transform is on
    // For now we are assuming all textures are perpendicular to z
    // We also do not handle rotation at the moment (should be ok - just rotate the dims vector
    // Why is the y like this, bleurgh
    glm::vec3 translation = m_transform->getWorldTranslation();

    float t = (translation.z - ray.m_origin.z) / ray.m_direction.z;
    glm::vec2 intersectPoint(ray.m_origin.x + t * ray.m_direction.x, ray.m_origin.y + t * ray.m_direction.y);

    return intersects(intersectPoint);
  }
}
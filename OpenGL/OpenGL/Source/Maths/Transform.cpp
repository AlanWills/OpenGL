#include "stdafx.h"

#include "Maths/Transform.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Transform::Transform(glm::mat4 localMatrix) :
    m_localMatrix(localMatrix)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Transform::translate(const glm::vec3& translation)
  {
    m_localMatrix[3].x += translation.x;
    m_localMatrix[3].y += translation.y;
    m_localMatrix[3].z += translation.z;
  }
}
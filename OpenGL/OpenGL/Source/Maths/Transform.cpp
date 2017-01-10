#include "stdafx.h"

#include "Maths/Transform.h"


namespace OpenGL
{
  // Initialize static variables
  Transform::Alloc Transform::m_allocator = Transform::Alloc();

  //------------------------------------------------------------------------------------------------
  Transform::Transform(glm::mat4 localMatrix) :
    m_parent(nullptr),
    m_localMatrix(localMatrix)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Transform::translate(const glm::vec2& translation)
  {
    m_localMatrix[3].x += translation.x;
    m_localMatrix[3].y += translation.y;
  }

  //------------------------------------------------------------------------------------------------
  void Transform::translate(const glm::vec3& translation)
  {
    m_localMatrix[3].x += translation.x;
    m_localMatrix[3].y += translation.y;
    m_localMatrix[3].z += translation.z;
  }

  //------------------------------------------------------------------------------------------------
  void Transform::setLocalTranslation(const glm::vec3& translation)
  {
    m_localMatrix[3].x = translation.x;
    m_localMatrix[3].y = translation.y;
    m_localMatrix[3].z = translation.z;
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getLocalTranslation() const
  {
    const glm::vec4& translation = m_localMatrix[3];
    return glm::vec3(translation.x, translation.y, translation.z);
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getWorldTranslation() const
  {
    const glm::vec4& translation = getWorldMatrix()[3];
    return glm::vec3(translation.x, translation.y, translation.z);
  }
}
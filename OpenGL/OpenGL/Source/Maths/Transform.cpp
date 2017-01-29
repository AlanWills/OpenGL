#include "stdafx.h"

#include "Maths/Transform.h"


namespace OpenGL
{
  // Initialize static variables
  Transform::Alloc Transform::m_allocator = Transform::Alloc();

  //------------------------------------------------------------------------------------------------
  Transform::Transform(glm::mat4 localMatrix) :
    m_parent(nullptr),
    m_rotation(0),
    m_translation(glm::zero<glm::vec3>()),
    m_scale(glm::one<glm::vec3>())
  {
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Transform::getLocalMatrix() const
  {
    glm::mat4 localMatrix = glm::scale(glm::mat4(), m_scale);
    localMatrix = glm::rotate(localMatrix, m_rotation, glm::vec3(0, 0, 1));
    localMatrix[3] = glm::vec4(m_translation, 1);

    return localMatrix;
  }

  //------------------------------------------------------------------------------------------------
  glm::mat4 Transform::getWorldMatrix() const
  {
    if (m_parent.get())
    {
      glm::mat4 worldMatrix = glm::scale(glm::mat4(), getWorldScale());
      worldMatrix = glm::rotate(worldMatrix, getWorldRotation(), glm::vec3(0, 0, 1));
      worldMatrix[3] = glm::vec4(getWorldTranslation(), 1);

      return worldMatrix;
    }

    return getLocalMatrix();
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getWorldTranslation() const
  {
    return m_parent.get() ? m_parent->getWorldTranslation() + m_translation : m_translation;
  }

  //------------------------------------------------------------------------------------------------
  glm::vec3 Transform::getWorldScale() const
  {
    return m_parent.get() ? m_parent->getWorldScale() * m_scale : m_scale;
  }

  //------------------------------------------------------------------------------------------------
  float Transform::getWorldRotation() const
  {
    return m_parent.get() ? m_parent->getWorldRotation() + m_rotation : m_rotation;
  }
}
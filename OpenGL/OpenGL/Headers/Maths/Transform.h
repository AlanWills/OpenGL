#pragma once

#include "OpenGL/GLHeaders.h"


namespace OpenGL
{
  /// A class representing a transformation in 3D space with various utility functions for manipulation and hierarchy.
  class Transform
  {
    public:
      Transform(glm::mat4 localMatrix = glm::mat4());

      glm::mat4 getWorldMatrix() const { return m_parent ? m_localMatrix * m_parent->getWorldMatrix() : m_localMatrix; }

      const glm::mat4& getLocalMatrix() const { return m_localMatrix; }
      void setLocalMatrix(const glm::mat4& localMatrix) { m_localMatrix = localMatrix; }

      void applyTransform(const glm::mat4& transform) { m_localMatrix *= transform; }
      
      void translate(const glm::vec2& translation);
      void translate(const glm::vec3& translation);

      glm::vec3 getTranslation() const;

      void setParent(Transform* parent) { m_parent = parent; }

    private:
      Transform* m_parent;
      glm::mat4 m_localMatrix;
  };
}
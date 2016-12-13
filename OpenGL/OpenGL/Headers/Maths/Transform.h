#pragma once

#include "GLHeaders.h"


namespace OpenGL
{
  /// A class representing a transformation in 3D space with various utility functions for manipulation and hierarchy.
  class Transform
  {
    public:
      Transform(glm::mat4 localMatrix = glm::mat4());

      const glm::mat4& getLocalMatrix() const { return m_localMatrix; }
      void setLocalMatrix(const glm::mat4& localMatrix) { m_localMatrix = localMatrix; }

      void translate(const glm::vec3& translation);

    private:
      glm::mat4 m_localMatrix;
  };
}
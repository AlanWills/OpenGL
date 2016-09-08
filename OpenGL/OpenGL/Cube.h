#pragma once

#include "GLHeaders.h"

#include <glm/gtc/matrix_transform.hpp>
#include <memory>

class Shader;

class Cube
{
public:
  Cube();
  ~Cube();

  /// \brief A function that preps the gl data ready for drawing multiple instances of this cube.
  /// Needs only be called once for multiple instances
  void beginDraw();

  /// \brief Performs the appropriate GL draw call
  void drawInstance(Shader& shader, const glm::mat4& transform);

  /// \brief A function that cleans up after drawing multiple instances of the cube
  void endDraw();

private:
  void glInitialize();

  // gl render data that we only need one copy of and can reuse over multiple cube instances
  std::unique_ptr<GLfloat> m_vertexAttributeData;
  GLuint m_vertexAttributeHandle;
  GLuint m_vertexBufferHandle;
  GLuint m_edgeBufferHandle;
};
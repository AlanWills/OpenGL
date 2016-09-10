#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "GLHeaders.h"

class Shader;
class Texture;

class SpriteRenderer
{

public:
  SpriteRenderer(Shader* shader);
  ~SpriteRenderer();

  void drawSprite(
    const Texture &texture, 
    const glm::vec2& position, 
    const glm::vec2& size = glm::vec2(10, 10), 
    GLfloat rotate = 0.0f, 
    const glm::vec4& color = glm::vec4(1.0f));

private:
  void initRenderData();

  // Don't use smart pointer as this shader is managed by the ResourceManager
  Shader* m_shader;
  GLuint m_vertexAttributeHandle;
};


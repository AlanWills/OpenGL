#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"


class SpriteRenderer
{
public:
  // Constructor (inits shaders/shapes)
  SpriteRenderer(Shader* shader);

  // Destructor
  ~SpriteRenderer();

  // Renders a defined quad textured with given sprite
  void drawSprite(
    const Texture2D* texture, 
    const glm::vec2& position,
    const glm::vec2& size = glm::vec2(10, 10), 
    GLfloat rotate = 0.0f, 
    const glm::vec3& color = glm::vec3(1.0f)) const;

private:
  // Initializes and configures the quad's buffer and vertex attributes
  void initRenderData();

  // Render state
  Shader* m_shader;
  GLuint m_quadVAO;
};

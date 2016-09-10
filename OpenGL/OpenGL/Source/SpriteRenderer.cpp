#include "SpriteRenderer.h"
#include "Camera.h"
#include "Texture.h"
#include "Shader.h"
#include "Debug.h"

//------------------------------------------------------------------------------------------------
SpriteRenderer::SpriteRenderer(Shader* shader)
: m_shader(shader)
{
}

//------------------------------------------------------------------------------------------------
SpriteRenderer::~SpriteRenderer()
{
}

//------------------------------------------------------------------------------------------------
void SpriteRenderer::initRenderData()
{
  // Configure VAO/VBO
  GLuint VBO;
  GLfloat vertices[] = {
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &m_vertexAttributeHandle);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(m_vertexAttributeHandle);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glCheckError();
}

//------------------------------------------------------------------------------------------------
void SpriteRenderer::drawSprite(
  const Texture &texture, 
  const glm::vec2& position,
  const glm::vec2& size, 
  GLfloat rotate,
  const glm::vec4& color)
{
  glCheckError();

  // Prepare transformations
  m_shader->use();
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  m_shader->setMatrix(model, MODEL_MATRIX);
  m_shader->setVector4(color, COLOUR);

  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(m_vertexAttributeHandle);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);

  glCheckError();
}
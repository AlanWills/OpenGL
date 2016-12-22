#include "stdafx.h"

#include "Rendering/SpriteRenderer.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(SpriteRenderer)

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer() :
    m_texture(nullptr),
    m_colour(1, 1, 1, 1),
    m_vbo(0),
    m_vao(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::~SpriteRenderer()
  {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::initialize()
  {
    Inherited::initialize();

    // Configure the vbo/vao
    GLfloat vertices[] = 
    {
      // Pos                // Tex
      0.5f,  0.5f, 1.0f, 1.0f,   // Top Right
      0.5f, -0.5f, 1.0f, 0.0f,   // Bottom Right
      -0.5f, -0.5f, 0.0f, 0.0f,   // Bottom Left
      -0.5f,  0.5f, 0.0f, 1.0f,   // Top Left
    };

    GLuint indices[] = {  // Note that we start from 0!
      0, 1, 3, // First Triangle
      1, 2, 3  // Second Triangle
    };

    // Generate the vertex attribute array for the shader
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    // Bind the buffer data to the graphics card
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Now reset the graphics card state
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::render(GLfloat lag)
  {
    Inherited::render(lag);

    // Only draw if we have a texture set
    if (m_texture)
    {
      Shader* spriteShader = GameManager::getRenderManager()->getSpriteShader();
      spriteShader->setVector4f("spriteColour", m_colour);

      glActiveTexture(GL_TEXTURE0);
      m_texture->bind();
      glUniform1i(glGetUniformLocation(spriteShader->getProgram(), "sprite"), 0);
      glCheckError();

      glBindVertexArray(m_vao);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      glCheckError();

      m_texture->unbind();
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setTexture(const std::string& textureStringId)
  {
    // Now load the texture from the ResourceManager
    // We can use fast interning as if it has been preloaded the string intern has already been calculated
    m_texture = GameManager::getResourceManager()->getTexture(internStringFast(textureStringId));
    ASSERT(m_texture);
  }
}
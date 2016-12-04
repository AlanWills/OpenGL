#include "stdafx.h"

#include "Components/Rendering/SpriteRenderer.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  // Initialise static variables
  StringId SpriteRenderer::s_spriteShaderId = internString("sprite");

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer() :
    m_texture(nullptr),
    m_shader(nullptr),
    m_vbo(0),
    m_vao(0),
    m_ebo(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::~SpriteRenderer()
  {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::init(StringId textureName)
  {
    // Configure the vbo/vao
    GLfloat vertices[] = {
      // Positions          // Colors           // Texture Coords
      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
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

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // Now reset the graphics card state
    glBindVertexArray(0);
    
    // Now load the texture from the ResourceManager
    m_texture = GameManager::getResourceManager()->getTexture(textureName);
    m_shader = GameManager::getResourceManager()->getShader(s_spriteShaderId);

    // Debug check
    ASSERT(m_texture);
    ASSERT(m_shader);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::render(GLfloat lag, const glm::mat4& modelMatrix)
  {
    // Set up the sprite shader
    m_shader->bind();

    glActiveTexture(GL_TEXTURE0);
    m_texture->bind();
    glUniform1i(glGetUniformLocation(m_shader->getProgram(), "ourTexture1"), 0);

    glActiveTexture(GL_TEXTURE1);
    m_texture->bind();
    glUniform1i(glGetUniformLocation(m_shader->getProgram(), "ourTexture2"), 1);

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Finish with our shader
    m_shader->unbind();
  }
}
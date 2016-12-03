#include "stdafx.h"

#include "Components/Rendering/SpriteRenderer.h"
#include "Game/GameManager.h"


namespace Engine
{
  // Initialise static variables
  StringId SpriteRenderer::s_spriteShaderId = internString("sprite");

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer() :
    m_texture(nullptr),
    m_shader(nullptr),
    m_vbo(0),
    m_vao(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::~SpriteRenderer()
  {
    glDeleteVertexArrays(1, &m_vao);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::init(StringId textureName)
  {
    // Configure the vbo/vao
    GLfloat vertices[] = 
    {
      // Pos      // Tex
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
    };

    // Bind the buffer data to the graphics card
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Now generate the vertex attribute array for the shader
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    // Now reset the graphics card state
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
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

    m_shader->setMatrix4("model", modelMatrix);
    m_shader->setVector4f("spriteColour", m_colour);

    m_texture->bind();

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    m_texture->unbind();

    // Finish with our shader
    m_shader->unbind();
  }
}
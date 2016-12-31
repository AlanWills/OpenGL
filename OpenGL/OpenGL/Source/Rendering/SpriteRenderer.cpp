#include "stdafx.h"

#include "Rendering/SpriteRenderer.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(SpriteRenderer)

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::SpriteRenderer() :
    m_texture(nullptr),
    m_transform(nullptr),
    m_colour(1, 1, 1, 1),
    m_vbo(0),
    m_vao(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  SpriteRenderer::~SpriteRenderer()
  {
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setupGLBuffers()
  {
    if (!m_texture.get())
    {
      ASSERT_FAIL();
      return;
    }

    float screenWidth = GameManager::getScreenManager()->getViewportWidth();
    float screenHeight = GameManager::getScreenManager()->getViewportHeight();

    // Scale the texture by the screen dimensions * 2 because we will have the quad centred on the middle and extending
    // In each direction by half
    float ratioX = m_texture->getWidth() / (screenWidth * 2);
    float ratioY = m_texture->getHeight() / (screenHeight * 2);

    // Configure the vbo/vao
    GLfloat vertices[] =
    {
      // Pos    // Tex
      ratioX,  ratioY, 0, 1.0f, 1.0f,   // Top Right
      ratioX, -ratioY, 0, 1.0f, 0.0f,   // Bottom Right
      -ratioX, -ratioY, 0, 0.0f, 0.0f,   // Bottom Left
      -ratioX,  ratioY, 0, 0.0f, 1.0f,   // Top Left
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Now reset the graphics card state
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::cleanupGLBuffers()
  {
    if (!m_texture.get() ||
         m_vao == 0 ||
         m_vbo == 0)
    {
      ASSERT_FAIL();
      return;
    }

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::awake()
  {
    Inherited::awake();

    ASSERT(getParent().get());
    m_transform = &getParent()->getTransform();
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::render(GLfloat lag)
  {
    Inherited::render(lag);

    // Only draw if we have a texture set
    if (m_texture.get())
    {
      glCheckError();
      Handle<Shader> spriteShader = GameManager::getResourceManager()->getShader(internStringFast("sprite"));

      spriteShader->setVector4f("spriteColour", m_colour);
      spriteShader->setMatrix4("model", m_transform ? m_transform->getLocalMatrix() : glm::mat4());

      glActiveTexture(GL_TEXTURE0);
      m_texture->bind();
      glUniform1i(glGetUniformLocation(spriteShader->getProgram(), "sprite"), 0);
      glCheckError();

      glBindVertexArray(m_vao);
      glCheckError();
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
      glCheckError();

      m_texture->unbind();
    }
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::die()
  {
    Inherited::die();

    cleanupGLBuffers();
  }

  //------------------------------------------------------------------------------------------------
  void SpriteRenderer::setTexture(const std::string& textureString)
  {
    // Now load the texture from the ResourceManager
    // We can use fast interning as if it has been preloaded the string intern has already been calculated
    m_texture = GameManager::getResourceManager()->getTexture(internStringFast(textureString));
    ASSERT(m_texture.get());

    setupGLBuffers();
  }
}
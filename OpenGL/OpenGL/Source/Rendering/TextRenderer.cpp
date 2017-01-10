#include "stdafx.h"

#include "Rendering/TextRenderer.h"
#include "Resources/Shader.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  REGISTER_COMPONENT(TextRenderer);

  //------------------------------------------------------------------------------------------------
  TextRenderer::TextRenderer() :
    m_font(nullptr),
    m_text(""),
    m_colour(1, 1, 1, 1),
    m_scale(1),
    m_vbo(0),
    m_vao(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  TextRenderer::~TextRenderer()
  {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 5, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (!m_font.get())
    {
      // If we have not created a font, set a default one
      setFont("Arial");
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::render(GLfloat lag)
  {
    Inherited::render(lag);

    if (m_font.get() && !m_text.empty())
    {
      glCheckError();
      Handle<Shader> textShader = GameManager::getResourceManager()->getShader(internStringFast("text"));
      textShader->setVector4f("textColour", m_colour);

      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(m_vao);

      Handle<GameObject> parent = getParent();
      ASSERT(parent.get());

      glm::mat4 modelMatrix;
      modelMatrix[3] = getParent()->getTransform()->getWorldMatrix()[3];
      textShader->setMatrix4("model", modelMatrix);

      const glm::vec2& size = m_font->measureString(m_text);

      GLfloat x = -size.x * 0.5f;
      GLfloat y = 0;

      for (char letter : m_text)
      {
        const Character& character = m_font->getCharacter(letter);

        GLfloat xpos = x + character.m_bearing.x * m_scale;
        GLfloat ypos = y - (character.m_size.y - character.m_bearing.y) * m_scale;

        GLfloat w = character.m_size.x * m_scale;
        GLfloat h = character.m_size.y * m_scale;

        // Update VBO for each character
        GLfloat vertices[30] = {
          xpos,     ypos + h,   0, 0, 0,
          xpos,     ypos,       0, 0, 1,
          xpos + w, ypos,       0, 1, 1,
                                
          xpos,     ypos + h,   0, 0, 0,
          xpos + w, ypos,       0, 1, 1,
          xpos + w, ypos + h,   0, 1, 0,
        };

        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, character.m_textureId);

        // Update content of m_vbo memory
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (character.m_advance >> 6) * m_scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
      }

      glBindVertexArray(0);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::setFont(const std::string& fontString)
  {
    // Now load the font from the ResourceManager
    // We can use fast interning as if it has been preloaded the string intern has already been calculated
    m_font = GameManager::getResourceManager()->getFont(internStringFast(fontString));
    ASSERT(m_font.get());
  }
}
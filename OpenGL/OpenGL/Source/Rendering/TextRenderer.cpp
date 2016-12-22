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
  void TextRenderer::initialize()
  {
    Inherited::initialize();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  //------------------------------------------------------------------------------------------------
  void TextRenderer::render(GLfloat lag)
  {
    Inherited::render(lag);

    if (m_font && !m_text.empty())
    {
      Shader* textShader = GameManager::getRenderManager()->getTextShader();
      textShader->setVector4f("textColour", m_colour);

      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(m_vao);

      GLfloat x = 0;
      GLfloat y = 25;
      GLfloat scale = 1;

      for (char letter : m_text)
      {
        const Character& character = m_font->getCharacter(letter);

        GLfloat xpos = x + character.m_bearing.x * scale;
        GLfloat ypos = y - (character.m_size.y - character.m_bearing.y) * scale;

        GLfloat w = character.m_size.x * scale;
        GLfloat h = character.m_size.y * scale;

        // Update VBO for each character
        GLfloat vertices[6][4] = {
          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos,     ypos,       0.0, 1.0 },
          { xpos + w, ypos,       1.0, 1.0 },

          { xpos,     ypos + h,   0.0, 0.0 },
          { xpos + w, ypos,       1.0, 1.0 },
          { xpos + w, ypos + h,   1.0, 0.0 }
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
        x += (character.m_advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
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
    ASSERT(m_font);
  }
}
#pragma once

#include "GLHeaders.h"
#include "ft2build.h"
#include FT_FREETYPE_H 

#include <map>


namespace OpenGL
{

struct Character
{
  GLuint      m_textureId;    // ID handle of the glyph texture
  glm::ivec2  m_size;         // Size of glyph
  glm::ivec2  m_bearing;      // Offset from baseline to left/top of glyph
  GLuint      m_advance;      // Offset to advance to next glyph
};

class Font
{
  public:
    Font();
    ~Font();

    void generate(const std::string& trueTypeFontFullPath, float height = 12);

    float getHeight() const { return m_height; }
    const Character& getCharacter(GLchar character) const;

  private:
    std::map<GLchar, Character> m_characters;
    float m_height;
};

}
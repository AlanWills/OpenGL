#pragma once

#include "GLHeaders.h"
#include "Resources/Texture2D.h"
#include "Resources/Shader.h"
#include "StringInterning/StringId.h"
#include "Objects/Component.h"

#include <string>

namespace OpenGL
{
// A class which is responsible for rendering a texture using the sprite shader
class SpriteRenderer : public Component
{
  public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    /// \brief Set up the gl buffers
    void initialize() override;
    void render(GLfloat lag) override;

    void setTexture(Kernel::StringId textureStringId);

    const glm::vec4& getColour() const { return m_colour; }
    void setColour(const glm::vec4& colour) { m_colour = colour; }

  private:
    Texture2D* m_texture;

    glm::vec4 m_colour;

    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_vao;
};

}
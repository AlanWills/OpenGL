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
  DECLARE_COMPONENT(SpriteRenderer, 10);

  public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    /// \brief Set up the gl buffers
    void initialize() override;
    void render(GLfloat lag) override;

    /// \brief Load a texture from the resource manager and set it as the texture to render on this sprite renderer
    void setTexture(const std::string& textureStringId);

    const glm::vec4& getColour() const { return m_colour; }
    void setColour(const glm::vec4& colour) { m_colour = colour; }

  private:
    typedef Component Inherited;

    Texture2D* m_texture;

    glm::vec4 m_colour;

    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_vao;

    friend class RenderManager;
};

}
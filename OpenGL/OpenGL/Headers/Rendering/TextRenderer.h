#pragma once

#include "StringInterning/StringId.h"
#include "Resources/Font.h"
#include "Objects/Component.h"


namespace OpenGL
{
// A class which is responsible for rendering text in a specific font
class TextRenderer : public Component
{
  DECLARE_COMPONENT_WITH_MANAGER(TextRenderer, 10, RenderManager);

  public:
    TextRenderer();
    virtual ~TextRenderer();

    /// \brief Set up the gl buffers
    void initialize() override;
    void render(GLfloat lag) override;

    /// \brief Loads a font from the resource manager and sets it to be the font this renderer uses
    void setFont(const std::string& fontString);

    /// \brief Sets the text which will be rendered
    void setText(const std::string& text) { m_text = text; }

    const glm::vec4& getColour() const { return m_colour; }
    void setColour(const glm::vec4& colour) { m_colour = colour; }

    void setScale(GLfloat scale) { m_scale = scale; }

  private:
    typedef Component Inherited;

    Handle<Font> m_font;
    std::string m_text;

    glm::vec4 m_colour;
    GLfloat m_scale;

    GLuint m_vbo;
    GLuint m_vao;
};

}
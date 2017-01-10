#pragma once

#include "Resources/Font.h"
#include "Renderer.h"


namespace OpenGL
{
// A class which is responsible for rendering text in a specific font
class TextRenderer : public Renderer
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, TextRenderer, 10, RenderManager);

  public:
    void initialize(Handle<Component> allocHandle) override;
    void render(GLfloat lag) override;

    /// \brief Loads a font from the resource manager and sets it to be the font this renderer uses
    void setFont(const std::string& fontString);

    /// \brief Sets the text which will be rendered
    void setText(const std::string& text) { m_text = text; }

    glm::vec2 getDimensions() const override;

  protected:
    void setupGLBuffers() override;

  private:
    typedef Renderer Inherited;

    Handle<Font> m_font;
    std::string m_text;
};

}
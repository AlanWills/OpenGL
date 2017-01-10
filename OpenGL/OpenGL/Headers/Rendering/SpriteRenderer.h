#pragma once

#include "Resources/Texture2D.h"
#include "Renderer.h"

#include <string>


namespace OpenGL
{
// A class which is responsible for rendering a texture using the sprite shader
class SpriteRenderer : public Renderer
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, SpriteRenderer, 10, RenderManager);

  public:
    void render(GLfloat lag) override;

    /// \brief Load a texture from the resource manager and set it as the texture to render on this sprite renderer
    void setTexture(const std::string& textureString);

    /// \brief Returns the scaled dimensions of the texture being rendered
    glm::vec2 getDimensions() const override;

    /// \brief Returns the width and height of the texture being rendered
    glm::vec2 getTextureDimensions() const;

  protected:
    /// \brief Uses the set texture to allocate buffers on the graphics card
    void setupGLBuffers() override;

    /// \brief Deallocate all the buffered data on the graphics card
    void cleanupGLBuffers() override;

    Handle<Texture2D> m_texture;

  private:
    typedef Renderer Inherited;

    GLuint m_ebo;
};

}
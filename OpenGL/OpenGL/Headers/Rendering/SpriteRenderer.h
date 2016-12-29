#pragma once

#include "OpenGL/GLHeaders.h"
#include "Resources/Texture2D.h"
#include "Resources/Shader.h"
#include "StringInterning/StringId.h"
#include "Objects/Component.h"
#include "Maths/Transform.h"

#include <string>


namespace OpenGL
{
// A class which is responsible for rendering a texture using the sprite shader
class SpriteRenderer : public Component
{
  DECLARE_SCREEN_AND_WORLD_COMPONENT_WITH_MANAGER(SpriteRenderer, 10, RenderManager);

  public:
    SpriteRenderer();
    virtual ~SpriteRenderer();

    void render(GLfloat lag) override;
    void die() override;

    /// \brief Load a texture from the resource manager and set it as the texture to render on this sprite renderer
    void setTexture(const std::string& textureStringId);

    /// \brief Set the model transform of the sprite we are drawing
    void setTransform(Transform* transform) { m_transform = transform; }

    const glm::vec4& getColour() const { return m_colour; }
    void setColour(const glm::vec4& colour) { m_colour = colour; }

  private:
    typedef Component Inherited;

    /// \brief Uses the set texture to allocate buffers on the graphics card
    void setupGLBuffers();

    /// \brief Deallocate all the buffered data on the graphics card
    void cleanupGLBuffers();

    Handle<Texture2D> m_texture;

    glm::vec4 m_colour;
    Transform* m_transform;

    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_vao;
};

}
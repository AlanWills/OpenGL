#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

/// A base class for all renderers in the engine
class Renderer : public Component
{
  public:
    Renderer();
    virtual ~Renderer();

    void die() override;

    const glm::vec4& getColour() const { return m_colour; }
    void setColour(const glm::vec4& colour) { m_colour = colour; }

    /// \brief Returns the to scale dimensions of the object being rendered
    virtual glm::vec2 getDimensions() const = 0;
  
    void setScale(const glm::vec2& scale) { m_scale = scale; }

  protected:
    /// \brief Generates the vertex arrays and buffers for the m_vao and m_vbo objects
    virtual void setupGLBuffers();

    /// \brief Deletes the vertex arrays and buffers for the m_vao and m_vbo objects
    virtual void cleanupGLBuffers();

    GLuint m_vbo;
    GLuint m_vao;
    
    glm::vec4 m_colour;
    glm::vec2 m_scale;

  private:
    typedef Component Inherited;
};

}
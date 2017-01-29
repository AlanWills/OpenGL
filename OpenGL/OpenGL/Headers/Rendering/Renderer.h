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

    /// \brief Returns the size of the texture being rendered multiplied by the attached object's scale
    virtual glm::vec2 getDimensions() const = 0;
  
  protected:
    /// \brief Generates the vertex arrays and buffers for the m_vao and m_vbo objects
    virtual void setupGLBuffers();

    /// \brief Deletes the vertex arrays and buffers for the m_vao and m_vbo objects
    virtual void cleanupGLBuffers();

    void bindVertexArray() const { glBindVertexArray(m_vao); }
    void bindVertexBuffer() const { glBindBuffer(GL_ARRAY_BUFFER, m_vbo); }

  private:
    typedef Component Inherited;

    GLuint m_vbo;
    GLuint m_vao;

    glm::vec4 m_colour;
};

}
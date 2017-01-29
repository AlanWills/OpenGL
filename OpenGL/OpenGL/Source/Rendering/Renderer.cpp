#include "stdafx.h"

#include "Rendering/Renderer.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Renderer::Renderer() :
    m_colour(1, 1, 1, 1),
    m_vbo(0),
    m_vao(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  Renderer::~Renderer()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Renderer::setupGLBuffers()
  {
    // Generate the vertex attribute array for the renderer
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
  }

  //------------------------------------------------------------------------------------------------
  void Renderer::cleanupGLBuffers()
  {
    if (m_vao == 0 ||
        m_vbo == 0)
    {
      ASSERT_FAIL();
      return;
    }

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
  }

  //------------------------------------------------------------------------------------------------
  void Renderer::die()
  {
    Inherited::die();

    cleanupGLBuffers();
  }
}
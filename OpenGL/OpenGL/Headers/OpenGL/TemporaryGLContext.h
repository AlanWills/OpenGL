#pragma once

#include "GLHeaders.h"
#include "DebugUtils/Debug.h"

// Temporary context that can be used in places where GL misbehaves across dll boundaries
// A good example of this is in compiling shaders in unit tests - for now it just does not seem to work
// MAKE SURE THIS IS CREATED ON THE FUNCTION SCOPE STACK ONLY

namespace OpenGL
{

class TemporaryGLContext
{
  public:
    TemporaryGLContext() :
      m_window(nullptr)
    {
      m_window = glfwCreateWindow(1, 1, "Temp", nullptr, nullptr);
      glfwMakeContextCurrent(m_window);

      glewExperimental = GL_TRUE;
      GLenum glewError = glewInit();
      ASSERT(glewError == GLEW_OK);
      const GLubyte* error = glewGetErrorString(glewError);
    }

    ~TemporaryGLContext()
    {
      glfwDestroyWindow(m_window);
    }

  private:
    GLFWwindow* m_window;
};

};
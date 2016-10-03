#include "stdafx.h"

#include "OpenGL/OpenGLContext.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  OpenGLContext::OpenGLContext()
  {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glCheckError();
    glewExperimental = GL_TRUE;
    glewInit();

    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    // See if there are any other errors on the stack
    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLContext::~OpenGLContext()
  {
    glfwTerminate();
  }
}
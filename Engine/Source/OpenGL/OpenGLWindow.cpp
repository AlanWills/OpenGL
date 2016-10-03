#include "stdafx.h"

#include "OpenGL/OpenGLWindow.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(GLfloat screenWidth, GLfloat screenHeight) :
    m_width(screenWidth),
    m_height(screenHeight),
    m_window(nullptr)
  {
    initGLFW();
    initWindow();
    initGLEW();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow() :
    m_width(0),
    m_height(0),
    m_window(nullptr)
  {
    initGLFW();

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_width = mode->width;
    m_height = mode->height;

    initWindow();
    initGLEW();
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::initGLFW()
  {
    // For some reason GLFW REALLY does not like being setup in this dll

    /*assert(glfwInit() == GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glCheckError();*/
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::initWindow()
  {
    m_window = glfwCreateWindow(m_width, m_height, "Breakout", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    // OpenGL configuration
    glViewport(0, 0, m_width, m_height);
    enableViewportFlag(GL_CULL_FACE);
    enableViewportFlag(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::initGLEW()
  {
    // For some reason GLFW REALLY does not like being setup in this dll

    //glewExperimental = GL_TRUE;
    //glewInit();

    //glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    //// See if there are any other errors on the stack
    //glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::~OpenGLWindow()
  {
    glfwDestroyWindow(m_window);
  }
}
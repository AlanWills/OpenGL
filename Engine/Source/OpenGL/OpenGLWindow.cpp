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
    initWindow();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow() :
    m_width(0),
    m_height(0),
    m_window(nullptr)
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_width = mode->width;
    m_height = mode->height;

    initWindow();
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
  OpenGLWindow::~OpenGLWindow()
  {
    glfwDestroyWindow(m_window);
  }
}
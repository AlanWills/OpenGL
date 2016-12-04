#include "stdafx.h"

#include "OpenGL/OpenGLWindow.h"

namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(GLfloat screenWidth, GLfloat screenHeight, ScreenMode screenMode) :
    m_width(screenWidth),
    m_height(screenHeight),
    m_window(nullptr)
  {
    initWindow(screenMode);
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::OpenGLWindow(ScreenMode screenMode) :
    m_width(0),
    m_height(0),
    m_window(nullptr)
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_width = mode->width;
    m_height = mode->height;

    initWindow(screenMode);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::initWindow(ScreenMode screenMode)
  {
    m_window = glfwCreateWindow(m_width, m_height, "Rebak Out", nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    // OpenGL configuration
    glViewport(0, 0, m_width, m_height);
    /*enableViewportFlag(GL_CULL_FACE);
    enableViewportFlag(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

    setScreenMode(screenMode);

    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow::~OpenGLWindow()
  {
    glfwDestroyWindow(m_window);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLWindow::setScreenMode(ScreenMode screenMode)
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int x, y;
    glfwGetWindowPos(m_window, &x, &y);

    glfwSetWindowMonitor(m_window, screenMode == kFullScreen ? glfwGetPrimaryMonitor() : nullptr, x, y, m_width, m_height, mode->refreshRate);
  }
}
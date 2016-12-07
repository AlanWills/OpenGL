#include "stdafx.h"

#include "Viewport/OpenGLViewport.h"

namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  OpenGLViewport::OpenGLViewport(GLfloat screenWidth, GLfloat screenHeight, ScreenMode screenMode) :
    m_width(screenWidth),
    m_height(screenHeight),
    m_viewport(nullptr),
    m_camera(new Camera())
  {
    initWindow(screenMode);
  }

  //------------------------------------------------------------------------------------------------
  OpenGLViewport::OpenGLViewport(ScreenMode screenMode) :
    m_width(0),
    m_height(0),
    m_viewport(nullptr),
    m_camera(new Camera())
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_width = mode->width;
    m_height = mode->height;

    initWindow(screenMode);
  }

  //------------------------------------------------------------------------------------------------
  OpenGLViewport::~OpenGLViewport()
  {
    glfwDestroyWindow(m_viewport);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLViewport::initWindow(ScreenMode screenMode)
  {
    m_viewport = glfwCreateWindow(m_width, m_height, "Rebak Out", nullptr, nullptr);
    glfwMakeContextCurrent(m_viewport);

    // OpenGL configuration
    glViewport(0, 0, m_width, m_height);
    /*enableViewportFlag(GL_CULL_FACE);
    enableViewportFlag(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

    setScreenMode(screenMode);

    glCheckError();
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLViewport::setScreenMode(ScreenMode screenMode)
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    int x, y;
    glfwGetWindowPos(m_viewport, &x, &y);

    glfwSetWindowMonitor(m_viewport, screenMode == kFullScreen ? glfwGetPrimaryMonitor() : nullptr, x, y, m_width, m_height, mode->refreshRate);
  }

  //------------------------------------------------------------------------------------------------
  Camera* OpenGLViewport::getCamera() const
  {
    ASSERT(m_camera.get());
    return m_camera.get();
  }
}
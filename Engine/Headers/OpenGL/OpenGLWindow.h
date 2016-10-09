#pragma once

#include "DllExport.h"
#include "GLHeaders.h"
#include "DebugUtils/Debug.h"

namespace Engine
{

// A class responsible for creating an OpenGL window and viewport
class DllExport OpenGLWindow
{
  public:
    enum ScreenMode
    {
      kWindowed,
      kFullScreen
    };

    OpenGLWindow(GLfloat windowWidth, GLfloat windowHeight, ScreenMode screenMode = kWindowed);
    OpenGLWindow(ScreenMode screenMode = kWindowed);

    ~OpenGLWindow();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    GLFWwindow* getGLWindow() const { return m_window; }

    inline void enableViewportFlag(GLenum flag) { glEnable(flag); }

    void setScreenMode(ScreenMode screenMode);
    bool isFullScreen() const { return glfwGetWindowMonitor(m_window) ? true : false; }

  private:
    void initWindow(ScreenMode screenMode);

    int m_width;
    int m_height;

    GLFWwindow* m_window;
};

};
#pragma once

#include "DllExport.h"
#include "GLHeaders.h"

namespace Engine
{

// A class responsible for creating an OpenGL window and viewport
class DllExport OpenGLWindow
{
  public:
    OpenGLWindow(GLfloat windowWidth, GLfloat windowHeight);
    OpenGLWindow();

    ~OpenGLWindow();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    GLFWwindow* getGLWindow() const { return m_window; }

    inline void enableViewportFlag(GLenum flag) { glEnable(flag); }

  private:
    void initWindow();

    int m_width;
    int m_height;

    GLFWwindow* m_window;
};

};
#pragma once

#include "OpenGL/GLHeaders.h"
#include "DebugUtils/Debug.h"
#include "Camera.h"


namespace OpenGL
{

// A class responsible for creating an OpenGL window and viewport
class OpenGLViewport
{
  public:
    enum ScreenMode
    {
      kWindowed,
      kFullScreen
    };

    OpenGLViewport(GLfloat windowWidth, GLfloat windowHeight, ScreenMode screenMode = kWindowed);
    OpenGLViewport(ScreenMode screenMode = kWindowed);

    ~OpenGLViewport();

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

    GLFWwindow* getGLWindow() const { return m_viewport; }
    Camera* getCamera() const;

    inline void enableViewportFlag(GLenum flag) { glEnable(flag); }

    void setScreenMode(ScreenMode screenMode);
    bool isFullScreen() const { return glfwGetWindowMonitor(m_viewport) ? true : false; }

    void handleInput(GLfloat elapsedGameTime);
    void update(GLfloat secondsPerUpdate);

  private:
    void initWindow(ScreenMode screenMode);

    int m_width;
    int m_height;

    GLFWwindow* m_viewport;
    
    std::unique_ptr<Camera> m_camera;
};

};
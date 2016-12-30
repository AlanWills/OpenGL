#include "stdafx.h"

#include "Viewport/OpenGLViewport.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  OpenGLViewport::OpenGLViewport(GLfloat screenWidth, GLfloat screenHeight, ScreenMode screenMode) :
    m_width(screenWidth),
    m_height(screenHeight),
    m_viewport(nullptr),
    m_camera(new Camera(screenWidth / screenHeight, 0.1f, 100, glm::vec3(0, 0, 5), glm::vec3(0, 0, -1)))
  {
    initWindow(screenMode);
  }

  //------------------------------------------------------------------------------------------------
  OpenGLViewport::OpenGLViewport(ScreenMode screenMode) :
    m_width(0),
    m_height(0),
    m_viewport(nullptr),
    m_camera(nullptr)
  {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    m_width = mode->width;
    m_height = mode->height;

    m_camera.reset(new Camera(m_width / m_height, 0.1f, 100, glm::vec3(0, 0, 1), glm::vec3(0, 0, -1)));

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
    /*enableViewportFlag(GL_CULL_FACE);*/
    enableViewportFlag(GL_BLEND);
    enableViewportFlag(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    setScreenMode(screenMode);

    glCheckError();

    getCamera()->initialize();
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLViewport::handleInput(GLfloat elapsedGameTime)
  {
    // Check to see whether we should exit
    if (GameManager::getInputManager()->getKeyboard()->isKeyPressed(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(m_viewport, GL_TRUE);
    }

    //getCamera()->handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void OpenGLViewport::update(GLfloat secondsPerUpdate)
  {
    getCamera()->update(secondsPerUpdate);
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
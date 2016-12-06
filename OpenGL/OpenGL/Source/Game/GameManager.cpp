#include "stdafx.h"

#include "Game/GameManager.h"


namespace OpenGL
{
  // Initialise static variables
  std::unique_ptr<OpenGLWindow> GameManager::m_window(nullptr);
  std::unique_ptr<ResourceManager> GameManager::m_resourceManager(new ResourceManager());
  std::unique_ptr<InputManager> GameManager::m_inputManager(new InputManager());
  std::unique_ptr<RenderManager> GameManager::m_renderManager(new RenderManager());
  std::unique_ptr<Clock> GameManager::m_gameClock(new Clock());

  //------------------------------------------------------------------------------------------------
  GameManager::GameManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  GameManager::~GameManager()
  {
    GLFW_TERMINATE();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::init()
  {
    GLFW_INIT();

    // Window must be created before any systems are initialised
    m_window.reset(new OpenGLWindow());

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, but it's been pain to figure this out, so just trust me)
    GLEW_INIT();

    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    getResourceManager()->init();
    getInputManager()->init();
    getRenderManager()->init();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::run()
  {
    // DeltaTime variables
    GLfloat lag = 0.0f;

    ASSERT(m_window.get());
    while (!glfwWindowShouldClose(m_window->getGLWindow()))
    {
      m_gameClock->update();

      GLfloat elapsedGameTime = m_gameClock->getElapsedDeltaTime();
      lag += elapsedGameTime;

      GLfloat gameSecondsPerUpdate = m_gameClock->getTimeScale() / m_gameClock->getTargetFramesPerSecond();

      glfwPollEvents();

      // Manage user input
      handleInput(elapsedGameTime);

      // We use a variable render fixed update loop
      while (lag >= gameSecondsPerUpdate)
      {
        // Update Game state
        update(gameSecondsPerUpdate);

        lag -= gameSecondsPerUpdate;
      }

      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Render
      render(lag);

      glfwSwapBuffers(m_window->getGLWindow());
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::handleInput(GLfloat elapsedGameTime)
  {
    // Check to see whether we should exit
    if (getInputManager()->getKeyboard()->isKeyPressed(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(m_window->getGLWindow(), GL_TRUE);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::update(GLfloat gameSecondsPerUpdate)
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::render(GLfloat lag)
  {
    getRenderManager()->render(lag);
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow* GameManager::getWindow()
  {
    ASSERT(m_window.get());
    return m_window.get();
  }

  //------------------------------------------------------------------------------------------------
  ResourceManager* GameManager::getResourceManager()
  {
    ASSERT(m_resourceManager.get());
    return m_resourceManager.get();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::setResourceManager(ResourceManager* resourceManager)
  {
    ASSERT(resourceManager);
    m_resourceManager.reset(resourceManager);
  }

  //------------------------------------------------------------------------------------------------
  InputManager* GameManager::getInputManager()
  {
    ASSERT(m_inputManager.get());
    return m_inputManager.get();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::setInputManager(InputManager* inputManager)
  {
    ASSERT(inputManager);
    m_inputManager.reset(inputManager);
  }

  //------------------------------------------------------------------------------------------------
  RenderManager* GameManager::getRenderManager()
  {
    ASSERT(m_renderManager.get());
    return m_renderManager.get();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::setRenderManager(RenderManager* renderManager)
  {
    ASSERT(renderManager);
    m_renderManager.reset(renderManager);
  }

  //------------------------------------------------------------------------------------------------
  Clock* GameManager::getGameClock()
  {
    ASSERT(m_gameClock.get());
    return m_gameClock.get();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::setGameClock(Clock* clock)
  {
    ASSERT(clock);
    m_gameClock.reset(clock);
  }
}
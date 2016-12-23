#include "stdafx.h"

#include "Game/GameManager.h"


namespace OpenGL
{
  // Initialise static variables
  std::unique_ptr<ResourceManager> GameManager::m_resourceManager(new ResourceManager());
  std::unique_ptr<ScreenManager> GameManager::m_screenManager(new ScreenManager());
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
    // ScreenManager initialize MUST be called first - it sets up the opengl context
    getScreenManager()->initialize();
    getResourceManager()->initialize();
    getInputManager()->initialize();
    getRenderManager()->initialize();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::run()
  {
    // DeltaTime variables
    GLfloat lag = 0.0f;

    awake();

    while (!glfwWindowShouldClose(getScreenManager()->getViewport()->getGLWindow()))
    {
      m_gameClock->update();

      GLfloat elapsedGameTime = m_gameClock->getElapsedDeltaTime();
      GLfloat gameSecondsPerUpdate = m_gameClock->getTimeScale() / m_gameClock->getTargetFramesPerSecond();
      lag += elapsedGameTime;

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

      glfwSwapBuffers(getScreenManager()->getViewport()->getGLWindow());
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::awake()
  {
    getScreenManager()->awake();
    getInputManager()->awake();
    getRenderManager()->awake();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::handleInput(GLfloat elapsedGameTime)
  {
    getScreenManager()->handleInput(elapsedGameTime);
    getInputManager()->handleInput(elapsedGameTime);
    getRenderManager()->handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::update(GLfloat elapsedGameTime)
  {
    getScreenManager()->update(elapsedGameTime);
    getInputManager()->update(elapsedGameTime);
    getRenderManager()->update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::render(GLfloat lag)
  {
    getScreenManager()->render(lag);
    getInputManager()->render(lag);
    getRenderManager()->render(lag);
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
  ScreenManager* GameManager::getScreenManager()
  {
    ASSERT(m_screenManager.get());
    return m_screenManager.get();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::setScreenManager(ScreenManager* screenManager)
  {
    ASSERT(screenManager);
    m_screenManager.reset(screenManager);
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
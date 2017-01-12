#include "stdafx.h"

#include "Game/GameManager.h"
#include "OpenAL/al.h"
#include "OpenAL/alc.h"


namespace OpenGL
{
  // Initialise static variables
  std::unique_ptr<ResourceManager> GameManager::m_resourceManager(new ResourceManager());
  std::unique_ptr<ScreenManager> GameManager::m_screenManager(new ScreenManager());
  std::unique_ptr<InputManager> GameManager::m_inputManager(new InputManager());
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
    // Initialize these managers with an empty allocator handler - they are taken care of here by unique_ptr
    getScreenManager()->initialize(Handle<Component>());
    getResourceManager()->initialize();
    getInputManager()->initialize(Handle<Component>());
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
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Render
      render(lag);

      glfwSwapBuffers(getScreenManager()->getViewport()->getGLWindow());
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::awake()
  {
    getInputManager()->awake();
    getScreenManager()->awake();
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::handleInput(GLfloat elapsedGameTime)
  {
    getInputManager()->handleInput(elapsedGameTime);
    getScreenManager()->handleInput(elapsedGameTime);

    if (getInputManager()->getKeyboard()->isKeyDown(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(getScreenManager()->getViewport()->getGLWindow(), GL_TRUE);
    }
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::update(GLfloat elapsedGameTime)
  {
    getInputManager()->update(elapsedGameTime);
    getScreenManager()->update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::render(GLfloat lag)
  {
    getInputManager()->render(lag);
    getScreenManager()->render(lag);
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

  //------------------------------------------------------------------------------------------------
  void GameManager::exit()
  {
    glfwSetWindowShouldClose(getScreenManager()->getViewport()->getGLWindow(), GL_TRUE);
  }
}
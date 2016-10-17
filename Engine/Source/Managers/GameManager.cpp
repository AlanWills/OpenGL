#include "stdafx.h"

#include "Managers/GameManager.h"
#include "Input/InputManager.h"
#include "Resources/ResourceManager.h"
#include "Time/Clock.h"


namespace Engine
{
  // Initialise static variables
  std::unique_ptr<OpenGLWindow> GameManager::m_window(nullptr);

  //------------------------------------------------------------------------------------------------
  GameManager::GameManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void GameManager::init()
  {
    GLFW_INIT();

    // Window must be created before any systems are initialised
    m_window.reset(new OpenGLWindow());

    GLEW_INIT();
    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    ResourceManager::init();
    InputManager::init();
    Clock::init();
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow* GameManager::getWindow()
  {
    ASSERT(m_window.get());
    return m_window.get();
  }

  //------------------------------------------------------------------------------------------------
  GameManager::~GameManager()
  {
    GLFW_TERMINATE();
  }
}
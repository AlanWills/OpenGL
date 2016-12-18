#include "stdafx.h"

#include "Screens/ScreenManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ScreenManager::ScreenManager() :
    m_viewport(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  ScreenManager::~ScreenManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::initialize()
  {
    Inherited::initialize();

    GLFW_INIT();

    // Must create the viewport here
    m_viewport.reset(new OpenGLViewport());

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been pain to figure this out, so just trust me)
    GLEW_INIT();

    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::begin()
  {
    Inherited::begin();

    for (Screen* screen : m_screens)
    {
      screen->begin();
    }
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    getViewport()->handleInput(elapsedGameTime);
    
    m_screens.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    getViewport()->update(secondsPerUpdate);

    m_screens.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    m_screens.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  Screen* ScreenManager::allocateScreen()
  {
    if (!m_screens.canAllocate())
    {
      ASSERT_FAIL_MSG("Run out of screens.  Considering allocating a larger screen pool");
      return nullptr;
    }

    return m_screens.allocate();
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::transitionToScreen(Screen* screenToTransitionTo)
  {
    if (m_activeScreen)
    {
      m_activeScreen->die();
    }

    screenToTransitionTo->initialize();
    m_activeScreen = screenToTransitionTo;
  }

  //------------------------------------------------------------------------------------------------
  OpenGLViewport* ScreenManager::getViewport()
  {
    ASSERT(m_viewport.get());
    return m_viewport.get();
  }
}
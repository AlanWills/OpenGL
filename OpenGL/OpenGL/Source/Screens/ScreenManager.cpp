#include "stdafx.h"

#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ScreenManager::ScreenManager() :
    m_viewport(nullptr),
    m_screenFactory(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  ScreenManager::~ScreenManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    GLFW_INIT();

    // Must create the viewport here
    m_viewport.reset(new OpenGLViewport());

    // It's important that GLEW is initialized after the window is created (I have literally no fucking idea why, 
    // but it's been pain to figure this out, so just trust me)
    GLEW_INIT();

    glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

    m_screenFactory.reset(new ScreenFactory());

    transitionToScreen(getScreenFactory()->createStartupLogoScreen());
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::awake()
  {
    Inherited::awake();

    Screen::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    getViewport()->handleInput(elapsedGameTime);
    
    Screen::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    getViewport()->update(secondsPerUpdate);

    Screen::m_componentAllocator.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    Screen::m_componentAllocator.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::transitionToScreen(Handle<Screen> screenToTransitionTo)
  {
    if (m_activeScreen.get())
    {
      m_activeScreen->die();
    }

    screenToTransitionTo->initialize(screenToTransitionTo);
    m_activeScreen = screenToTransitionTo;
  }

  //------------------------------------------------------------------------------------------------
  OpenGLViewport* ScreenManager::getViewport() const
  {
    ASSERT(m_viewport.get());
    return m_viewport.get();
  }

  //------------------------------------------------------------------------------------------------
  ScreenFactory* ScreenManager::getScreenFactory() const
  {
    ASSERT(m_screenFactory.get());
    return m_screenFactory.get();
  }

  //------------------------------------------------------------------------------------------------
  void ScreenManager::setScreenFactory(ScreenFactory* screenFactory)
  {
    ASSERT(screenFactory);
    m_screenFactory.reset(screenFactory);
  }
}
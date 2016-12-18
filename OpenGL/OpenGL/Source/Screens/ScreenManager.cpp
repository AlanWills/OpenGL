#include "stdafx.h"

#include "Screens/ScreenManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  ScreenManager::ScreenManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  ScreenManager::~ScreenManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  Screen* ScreenManager::constructScreen()
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
}
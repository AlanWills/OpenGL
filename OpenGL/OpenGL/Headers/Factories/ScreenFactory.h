#pragma once

#include "Screens/Screen.h"


namespace OpenGL
{

class ScreenFactory
{
  public:
    ScreenFactory() { }
    ~ScreenFactory() { }

    Handle<Screen> createSplashScreen() const;
    Handle<Screen> createMainMenuScreen() const;

  private:
    template <typename T>
    Handle<T> allocateScreenAndTransition() const;
};

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T> ScreenFactory::allocateScreenAndTransition() const
{
  if (!MenuScreen::canAllocate())
  {
    ASSERT_FAIL();
    return Handle<T>();
  }

  Handle<T> screen = T::allocateAndInitialize();
  GameManager::getScreenManager()->transitionToScreen(screen);

  return screen;
}

}
#pragma once

#include "Screens/Screen.h"


namespace OpenGL
{

class ScreenFactory
{
  public:
    ScreenFactory() { }
    ~ScreenFactory() { }

    // Creation functions
    Handle<Screen> transitionToSplashScreen() const;
    Handle<Screen> transitionToMainMenuScreen() const;
    Handle<Screen> transitionToGameplayScreen() const;

  private:
    void transitionCallback(Handle<GameObject> sender);
    bool firing();
    bool notFiring() { return !firing(); }

    Handle<Screen> allocateScreenAndTransition() const;
};

}
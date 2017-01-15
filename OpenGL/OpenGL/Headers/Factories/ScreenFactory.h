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

    // Utility functions
    void addScreenBackground(const Handle<Screen>& screen, const std::string& relativeImagePath) const;

  private:
    void transitionCallback(Handle<GameObject> sender);

    Handle<Screen> allocateScreenAndTransition() const;
};

}
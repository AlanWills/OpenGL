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
    Handle<Screen> createSplashScreen() const;
    Handle<Screen> createMainMenuScreen() const;

    // Utility functions
    void addScreenBackground(const Handle<Screen>& screen, const std::string& relativeImagePath) const;

  private:
    Handle<Screen> allocateScreenAndTransition() const;
};

}
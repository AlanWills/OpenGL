#pragma once

#include "Screens/Screen.h"


namespace OpenGL
{

class ScreenFactory
{
  public:
    ScreenFactory() { }
    ~ScreenFactory() { }

    Handle<Screen> createStartupLogoScreen() const;
};

}
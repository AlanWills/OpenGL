#pragma once

#include "Memory/ComponentAllocator.h"
#include "Screen.h"


namespace OpenGL
{
#define SCREEN_POOL_SIZE 5

class ScreenManager : public Component
{
  public:
    ScreenManager();
    ~ScreenManager();

    /// \brief Allocates the memory for a new screen and returns a pointer to it, but does not call initialize.
    /// Will return nullptr if a screen could not be allocated
    /// Since this object has not had initialize called, it is still dead so will not be updated & drawn.
    Screen* constructScreen();

    /// \brief Sets the inputted screen as the now current main screen and calls initialize on the inputted screen.
    void transitionToScreen(Screen* screenToTransitionTo);

  private:
    typedef Component Inherited;

    ComponentAllocator<Screen, SCREEN_POOL_SIZE> m_screens;

    Screen* m_activeScreen;
};

}
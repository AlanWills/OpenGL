#pragma once

#include "Memory/ComponentAllocator.h"
#include "Viewport/OpenGLViewport.h"
#include "Screen.h"


namespace OpenGL
{
#define SCREEN_POOL_SIZE 5

class ScreenManager : public Component
{
  public:
    ScreenManager();
    ~ScreenManager();

    void initialize() override;
    void begin() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

    /// \brief Allocates the memory for a new screen and returns a pointer to it, but does not call initialize.
    /// Will return nullptr if a screen could not be allocated
    /// Since this object has not had initialize called, it is still dead so will not be updated & drawn.
    Screen* allocateScreen();

    /// \brief Sets the inputted screen as the now current main screen and calls initialize on the inputted screen.
    void transitionToScreen(Screen* screenToTransitionTo);

    /// \brief Get the window
    OpenGLViewport* getViewport();

    inline int getWindowWidth() { return getViewport()->getWidth(); }
    inline int getWindowHeight() { return getViewport()->getHeight(); }

  private:
    typedef Component Inherited;

    /// \brief The GL window context
    std::unique_ptr<OpenGLViewport> m_viewport;

    ComponentAllocator<Screen, SCREEN_POOL_SIZE> m_screens;

    Screen* m_activeScreen;
};

}
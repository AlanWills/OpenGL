#pragma once

#include "Memory/ComponentAllocator.h"
#include "Viewport/OpenGLViewport.h"
#include "Screen.h"


namespace OpenGL
{

class ScreenManager : public Component
{
  public:
    ScreenManager();
    ~ScreenManager();

    void initialize() override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

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

    Screen* m_activeScreen;
};

}
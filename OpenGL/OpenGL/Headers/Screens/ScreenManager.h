#pragma once

#include "Memory/ComponentAllocator.h"
#include "Viewport/OpenGLViewport.h"
#include "Factories/ScreenFactory.h"


namespace OpenGL
{

class ScreenManager : public Component
{
  public:
    ScreenManager();
    virtual ~ScreenManager();

    void initialize(const Handle<Component>& allocHandle) override;
    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;
    void update(GLfloat secondsPerUpdate) override;
    void render(GLfloat lag) override;

    /// \brief Sets the inputted screen as the now current main screen and calls initialize on the inputted screen.
    void transitionToScreen(const Handle<Screen>& screenToTransitionTo);

    /// \brief Get the window
    OpenGLViewport* getViewport() const;

    /// \brief Get the screen factory
    ScreenFactory* getScreenFactory() const;
    void setScreenFactory(ScreenFactory* screenFactory);

    /// \brief Get the current active screen
    const Handle<Screen>& getCurrentScreen() const { return m_activeScreen; }

    /// \brief Shorthand for obtaining the viewport width
    inline float getViewportWidth() { return getViewport()->getWidth(); }

    /// \brief Shorthand for obtaining the viewport height
    inline float getViewportHeight() { return getViewport()->getHeight(); }

    /// \brief Shorthand for obtaining the viewport width and height
    inline glm::vec2 getViewportDimensions() { return glm::vec2(getViewportWidth(), getViewportHeight()); }

    void exitCallback(Handle<GameObject> gameObject);

  private:
    typedef Component Inherited;

    /// \brief The GL window context
    std::unique_ptr<OpenGLViewport> m_viewport;

    /// \brief The screen factory which wraps up the logic of creating various screens
    std::unique_ptr<ScreenFactory> m_screenFactory;

    Handle<Screen> m_activeScreen;
};

}
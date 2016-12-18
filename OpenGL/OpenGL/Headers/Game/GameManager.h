#pragma once

#include "Viewport/OpenGLViewport.h"
#include "Resources/ResourceManager.h"
#include "Screens/ScreenManager.h"
#include "Input/InputManager.h"
#include "Rendering/RenderManager.h"
#include "Time/Clock.h"


namespace OpenGL
{

/// Grouper class for all of the game managers
/// Also contains general meta data about the game and window
class GameManager
{
  public:
    /// \brief Initialise all of the managers associated with the game
    static void init();

    /// \brief Get the window
    static OpenGLViewport* getViewport();

    /// \brief Begin our game loop
    static void run();

    static inline int getWindowWidth() { return getViewport()->getWidth(); }
    static inline int getWindowHeight() { return getViewport()->getHeight(); }

    /// \brief GameManager takes responsibility for managing the resource manager
    static void setResourceManager(ResourceManager* resourceManager);
    static ResourceManager* getResourceManager();

    /// \brief GameManager takes responsibility for managing the screen manager
    static void setScreenManager(ScreenManager* screenManager);
    static ScreenManager* getScreenManager();

    /// \brief GameManager takes responsibility for managing the input manager
    static void setInputManager(InputManager* resourceManager);
    static InputManager* getInputManager();

    static void setRenderManager(RenderManager* renderManager);
    static RenderManager* getRenderManager();

    /// \brief GameManager takes responsibility for manager the clock
    static void setGameClock(Clock* clock);
    static Clock* getGameClock();

  private:
    GameManager();
    ~GameManager();

    static void handleInput(GLfloat elapsedGameTime);
    static void update(GLfloat gameSecondsPerUpdate);
    static void render(GLfloat lag);

    /// \brief The GL window context
    static std::unique_ptr<OpenGLViewport> m_viewport;

    /// \brief The manager responsible for handling game resources
    static std::unique_ptr<ResourceManager> m_resourceManager;

    /// \brief The manager responsible for handling screens
    static std::unique_ptr<ScreenManager> m_screenManager;

    /// \brief The manager responsible for handling and processing human input
    static std::unique_ptr<InputManager> m_inputManager;

    /// \brief The manager responsible for handling all rendering to the gl window
    static std::unique_ptr<RenderManager> m_renderManager;

    /// \brief The game clock responsible for managing game time
    /// This clock can have it's speed altered to change the speed of the game, but not the game loop itself
    static std::unique_ptr<Clock> m_gameClock;
};

}
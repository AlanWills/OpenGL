#pragma once

#include "DllExport.h"
#include "OpenGL/OpenGLWindow.h"
#include "Resources/ResourceManager.h"
#include "Input/InputManager.h"


namespace Engine
{

/// Grouper class for all of the game managers
/// Also contains general meta data about the game and window
class DllExport GameManager
{
  public:
    /// \brief Initialise all of the managers associated with the game
    static void init();

    /// \brief Get the window
    static OpenGLWindow* getWindow();

    /// \brief Begin our game loop
    static void run();

    static inline int getWindowWidth() { return getWindow()->getWidth(); }
    static inline int getWindowHeight() { return getWindow()->getHeight(); }

    static ResourceManager* getResourceManager();

    /// \brief GameManager takes responsibility for managing the resource manager
    static void setResourceManager(ResourceManager* resourceManager);

    static InputManager* getInputManager();

    /// \brief GameManager takes responsibility for managing the input manager
    static void setInputManager(InputManager* resourceManager);

  private:
    GameManager();
    ~GameManager();

    static void handleInput(GLfloat elapsedGameTime);
    static void update(GLfloat gameSecondsPerUpdate);
    static void render(GLfloat lag);

    /// \brief The GL window context
    static std::unique_ptr<OpenGLWindow> m_window;

    /// \brief The manager responsible for handling game resources
    static std::unique_ptr<ResourceManager> m_resourceManager;

    /// \brief The manager responsible for handling and processing human input
    static std::unique_ptr<InputManager> m_inputManager;
};

}
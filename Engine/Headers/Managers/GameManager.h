#pragma once

#include "DllExport.h"
#include "OpenGL/OpenGLWindow.h"


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

    static void run();

    static inline int getWindowWidth() { return getWindow()->getWidth(); }
    static inline int getWindowHeight() { return getWindow()->getHeight(); }

  private:
    GameManager();
    ~GameManager();

    static void handleInput(GLfloat elapsedGameTime);
    static void update(GLfloat gameSecondsPerUpdate);
    static void render(GLfloat lag);

    static std::unique_ptr<OpenGLWindow> m_window;
};

}
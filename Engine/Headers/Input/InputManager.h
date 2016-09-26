#pragma once

#include "DllExport.h"
#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"

namespace Engine
{
  // A class which uses a service locator pattern to store and update various input modules
  // These can be obtained and set with static methods, but the logic of them is in the objects themselves rather than this class
  class DllExport InputManager
  {

  public:
    /// \brief Set up the keyboard and mouse objects and also set up the global window callback
    /// To receive messages from the message window pump
    static void init(GLFWwindow* window);

    static void update(GLfloat elapsedGameTime);

    /// \brief The input manager will take ownership of this object now
    static void setKeyboard(Keyboard* keyboard);

    /// \brief The input manager has ownership of the keyboard object
    static Keyboard* getKeyboard();

    /// \brief The input manager will take ownership of this object now
    static void setMouse(Mouse* mouse);

    /// \brief The input manager has ownership of the mouse object
    static Mouse* getMouse();

  private:
    InputManager();
    ~InputManager();

    static std::unique_ptr<Keyboard> m_keyboard;
    static std::unique_ptr<Mouse> m_mouse;
  };

  // Initialise the static members here
  std::unique_ptr<Keyboard> InputManager::m_keyboard(nullptr);
  std::unique_ptr<Mouse> InputManager::m_mouse(nullptr);
}
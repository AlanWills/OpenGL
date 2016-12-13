#pragma once

#include "Keyboard/Keyboard.h"
#include "Mouse/Mouse.h"

#include <memory.h>

namespace OpenGL
{
// A class which uses a service locator pattern to store and update various input modules
// These can be obtained and set with static methods, but the logic of them is in the objects themselves rather than this class
class InputManager
{
  public:
    InputManager();
    ~InputManager();

    /// \brief Set up the keyboard and mouse objects and also set up the global window callback
    /// To receive messages from the message window pump
    void init();

    void handleInput(GLfloat elapsedGameTime);

    /// \brief The input manager will take ownership of this object now
    void setKeyboard(Keyboard* keyboard);

    /// \brief The input manager has ownership of the keyboard object
    Keyboard* getKeyboard() const;

    /// \brief The input manager will take ownership of this object now
    void setMouse(Mouse* mouse);

    /// \brief The input manager has ownership of the mouse object
    Mouse* getMouse() const;

  private:
    std::unique_ptr<Keyboard> m_keyboard;
    std::unique_ptr<Mouse> m_mouse;
};

}
#pragma once

#include "Keyboards/Keyboard.h"

namespace Engine
{
  // A class which uses a service locator pattern to store and update various input modules
  // These can be obtained and set with static methods, but the logic of them is in the objects themselves rather than this class
  class InputManager
  {

  public:
    static void update(GLfloat elapsedGameTime);

    /// \brief The input manager will take ownership of this object now
    static void setKeyboard(Keyboard* keyboard);

    /// \brief The input manager has ownership of the keyboard object
    static Keyboard* getKeyboard();

  private:
    InputManager();
    ~InputManager();

    static std::unique_ptr<Keyboard> m_keyboard;
  };

  // Initialise the static keyboard member here
  std::unique_ptr<Keyboard> InputManager::m_keyboard(new Keyboard());
}
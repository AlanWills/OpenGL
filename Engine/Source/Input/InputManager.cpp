#include "stdafx.h"

#include "Input/InputManager.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  InputManager::InputManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  InputManager::~InputManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::update(GLfloat elapsedGameTime)
  {
    m_keyboard->update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::setKeyboard(Keyboard* keyboard)
  {
    assert(keyboard);
    m_keyboard.reset(keyboard);
  }

  //------------------------------------------------------------------------------------------------
  Keyboard* InputManager::getKeyboard()
  {
    return m_keyboard.get();
  }
}
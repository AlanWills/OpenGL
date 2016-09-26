#include "stdafx.h"

#include "Input/Mouse/Mouse.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Mouse::Mouse()
  {
    flush();

    for (int i = 0; i < MouseButton::kNumButtons; ++i)
    {
      m_previousButtons[i] = GL_FALSE;
    }
  }

  //------------------------------------------------------------------------------------------------
  Mouse::~Mouse()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::update(GLfloat elapsedGameTime)
  {
    // Swap the mouse button state buffers
    std::swap(m_previousButtons, m_currentButtons);

    flush();
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setButtonDown(MouseButton mouseButton)
  {
    m_currentButtons[mouseButton] = GL_TRUE;
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::setButtonUp(MouseButton mouseButton)
  {
    m_currentButtons[mouseButton] = GL_FALSE;
  }

  //------------------------------------------------------------------------------------------------
  GLboolean Mouse::isButtonDown(MouseButton mouseButton) const
  {
    return m_currentButtons[mouseButton];
  }

  //------------------------------------------------------------------------------------------------
  GLboolean Mouse::isButtonPressed(MouseButton mouseButton) const
  {
    return m_currentButtons[mouseButton] && !m_previousButtons[mouseButton];
  }

  //------------------------------------------------------------------------------------------------
  void Mouse::flush()
  {
    for (int i = 0; i < MouseButton::kNumButtons; ++i)
    {
      m_currentButtons[i] = GL_FALSE;
    }
  }
}
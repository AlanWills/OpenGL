#include "stdafx.h"

#include "Input/Mouse/Mouse.h"
#include "Game/GameManager.h"

namespace OpenGL
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
  void Mouse::handleInput(GLfloat elapsedGameTime)
  {
    // Set the previous mouse button states to be the current mouse button states
    for (int i = 0; i < MouseButton::kNumButtons; ++i)
    {
      m_previousButtons[i] = m_currentButtons[i];
    }
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

  //------------------------------------------------------------------------------------------------
  glm::vec2 Mouse::getMousePosition() const
  {
    double x = 0, y = 0;
    glfwGetCursorPos(GameManager::getScreenManager()->getViewport()->getGLWindow(), &x, &y);

    return glm::vec2(x, y);
  }
}
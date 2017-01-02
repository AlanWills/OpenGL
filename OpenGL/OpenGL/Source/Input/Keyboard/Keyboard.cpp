#include "stdafx.h"

#include "Input/Keyboard/Keyboard.h"
#include "Game/GameManager.h"

namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Keyboard::Keyboard()
  {
    // I think it is quicker to iterate over each contiguous array separately rather than at the same time
    // However I could be wrong - profile this maybe?
    flush();

    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      m_previousKeys[i] = 0;
    }
  }

  //------------------------------------------------------------------------------------------------
  Keyboard::~Keyboard()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::handleInput(GLfloat elapsedGameTime)
  {
    GLFWwindow* window = GameManager::getScreenManager()->getViewport()->getGLWindow();

    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      // Update the previous frame's keys with the contents of the current keys buffer
      m_previousKeys[i] = m_currentKeys[i];

      // Get the current state of the buttons
      m_currentKeys[i] = glfwGetKey(window, i);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::setKeyDown(int key)
  {
    assert(0 <= key && key < KEYBOARD_KEY_COUNT);
    m_currentKeys[key] = GL_TRUE;
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::setKeyUp(int key)
  {
    assert(0 <= key && key < KEYBOARD_KEY_COUNT);
    m_currentKeys[key] = GL_FALSE;
  }

  //------------------------------------------------------------------------------------------------
  GLboolean Keyboard::isKeyDown(int key) const
  {
    return m_currentKeys[key];
  }

  //------------------------------------------------------------------------------------------------
  GLboolean Keyboard::isKeyPressed(int key) const
  {
    return !m_currentKeys[key] && m_previousKeys[key];
  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::flush()
  {
    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      m_currentKeys[i] = GL_FALSE;
    }
  }
}
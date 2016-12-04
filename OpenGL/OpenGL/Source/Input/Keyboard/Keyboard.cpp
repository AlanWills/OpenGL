#include "stdafx.h"

#include "Input/Keyboard/Keyboard.h"

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
  void Keyboard::update(GLfloat elapsedGameTime)
  {
    // Update the previous frame's keys with the contents of the current keys buffer
    for (int i = 0; i < KEYBOARD_KEY_COUNT; ++i)
    {
      m_previousKeys[i] = m_currentKeys[i];
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
    return m_currentKeys[key] && !m_previousKeys[key];
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
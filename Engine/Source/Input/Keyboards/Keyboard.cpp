#include "stdafx.h"

#include "Input/Keyboards/Keyboard.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  Keyboard::Keyboard()
    : m_currentKeys(),
      m_previousKeys()
  {
    m_currentKeys.fill(GL_FALSE);
    m_previousKeys.fill(GL_FALSE);
  }

  //------------------------------------------------------------------------------------------------
  Keyboard::~Keyboard()
  {

  }

  //------------------------------------------------------------------------------------------------
  void Keyboard::update(GLfloat elapsedGameTime)
  {
    m_previousKeys.swap(m_currentKeys);
    m_currentKeys.fill(GL_FALSE);
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
}
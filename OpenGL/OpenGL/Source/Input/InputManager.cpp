#include "stdafx.h"

#include "Input/InputManager.h"
#include "Game/GameManager.h"
#include "Physics/RectangleCollider.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  InputManager::InputManager() :
    m_keyboard(new Keyboard()),
    m_mouse(new Mouse())
  {
  }

  //------------------------------------------------------------------------------------------------
  InputManager::~InputManager()
  {
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::awake()
  {
    Inherited::awake();

    RectangleCollider::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_keyboard->handleInput(elapsedGameTime);
    m_mouse->handleInput(elapsedGameTime);

    RectangleCollider::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    RectangleCollider::m_componentAllocator.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    RectangleCollider::m_componentAllocator.render(lag);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::die()
  {
    Inherited::die();

    RectangleCollider::m_componentAllocator.die();
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::setKeyboard(Keyboard* keyboard)
  {
    ASSERT(keyboard);
    m_keyboard.reset(keyboard);
  }

  //------------------------------------------------------------------------------------------------
  Keyboard* InputManager::getKeyboard() const
  {
    ASSERT(m_keyboard.get());
    return m_keyboard.get();
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::setMouse(Mouse* mouse)
  {
    ASSERT(mouse);
    m_mouse.reset(mouse);
  }

  //------------------------------------------------------------------------------------------------
  Mouse* InputManager::getMouse() const
  {
    ASSERT(m_mouse.get());
    return m_mouse.get();
  }
}
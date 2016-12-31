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
  // The global callback used to receive keyboard messages from the GLWindow
  void handleGLKeyboardMessages(GLFWwindow* window, int key, int scancode, int action, int mode)
  {
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
      if (action == GLFW_PRESS)
      {
        GameManager::getInputManager()->getKeyboard()->setKeyDown(key);
      }
      else if (action == GLFW_RELEASE)
      {
        GameManager::getInputManager()->getKeyboard()->setKeyUp(key);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    glfwSetKeyCallback(GameManager::getScreenManager()->getViewport()->getGLWindow(), handleGLKeyboardMessages);
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
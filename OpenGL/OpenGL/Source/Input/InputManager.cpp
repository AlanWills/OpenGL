#include "stdafx.h"

#include "Input/InputManager.h"
#include "Game/GameManager.h"


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
  void InputManager::initialize()
  {
    Inherited::initialize();

    glfwSetKeyCallback(GameManager::getScreenManager()->getViewport()->getGLWindow(), handleGLKeyboardMessages);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    m_keyboard->handleInput(elapsedGameTime);
    m_mouse->handleInput(elapsedGameTime);
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
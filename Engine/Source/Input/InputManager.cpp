#include "stdafx.h"

#include "Input/InputManager.h"

namespace Engine
{
  InputManager::InputManager()
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
        InputManager::getKeyboard()->setKeyDown(key);
      }
      else if (action == GLFW_RELEASE)
      {
        InputManager::getKeyboard()->setKeyUp(key);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::init(GLFWwindow* window)
  {
    glfwSetKeyCallback(window, handleGLKeyboardMessages);

    setKeyboard(new Keyboard());
    setMouse(new Mouse());
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::update(GLfloat elapsedGameTime)
  {
    s_keyboard->update(elapsedGameTime);
    s_mouse->update(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::setKeyboard(Keyboard* keyboard)
  {
    assert(keyboard);
    s_keyboard.reset(keyboard);
  }

  //------------------------------------------------------------------------------------------------
  Keyboard* InputManager::getKeyboard()
  {
    assert(s_keyboard.get());
    return s_keyboard.get();
  }

  //------------------------------------------------------------------------------------------------
  void InputManager::setMouse(Mouse* mouse)
  {
    assert(mouse);
    s_mouse.reset(mouse);
  }

  //------------------------------------------------------------------------------------------------
  Mouse* InputManager::getMouse()
  {
    assert(s_mouse.get());
    return s_mouse.get();
  }
}
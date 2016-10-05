#include "stdafx.h"

#include "Input/Keyboard/NullKeyboard.h"

using namespace Engine;

namespace TestEngine
{		
	TEST_CLASS(TestNullKeyboard)
	{
	public:
		
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_IsKeyDown)
    {
      // NullKeyboard should return false no matter what state the keyboard is actually in
      NullKeyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_SPACE));

      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_IsKeyPressed)
    {
      // NullKeyboard should return false no matter what state the keyboard is actually in
      NullKeyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_SPACE));

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_C));
    }
	};
}
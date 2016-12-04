#include "stdafx.h"

#include "Input/Keyboard/Keyboard.h"

using namespace OpenGL;

namespace TestEngine
{		
	TEST_CLASS(TestKeyboard)
	{
	public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_SetKeyDown_NoError)
		{
      // Just check we don't get a really bad error like a nullptr exception when using this function
      Keyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_SetKeyUp_NoError)
    {
      // Just check we don't get a really bad error like a nullptr exception when using this function
      Keyboard keyboard;
      keyboard.setKeyUp(GLFW_KEY_A);
      keyboard.setKeyUp(GLFW_KEY_SPACE);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_IsKeyDown)
    {
      Keyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_SPACE));

      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_IsKeyPressed)
    {
      // Since our keyboard begins with both buffered arrays being false we do not need to call update
      Keyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_SPACE));

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_Flush)
    {
      Keyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      // Sanity check
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_SPACE));
      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_SPACE));

      // Flush now so that all the above calls should now fail
      keyboard.flush();

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_C));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_B));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_C));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Keyboard_Update)
    {
      Keyboard keyboard;
      keyboard.setKeyDown(GLFW_KEY_A);
      keyboard.setKeyUp(GLFW_KEY_SPACE);

      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_SPACE));
      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_A));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_SPACE));

      keyboard.update(0);

      keyboard.setKeyUp(GLFW_KEY_A);
      keyboard.setKeyDown(GLFW_KEY_SPACE);

      Assert::IsFalse(keyboard.isKeyPressed(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyPressed(GLFW_KEY_SPACE));
      Assert::IsFalse(keyboard.isKeyDown(GLFW_KEY_A));
      Assert::IsTrue(keyboard.isKeyDown(GLFW_KEY_SPACE));
    }
	};
}
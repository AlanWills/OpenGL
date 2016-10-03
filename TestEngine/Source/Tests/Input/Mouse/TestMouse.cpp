#include "stdafx.h"

#include "CppUnitTest.h"
#include "Input/Mouse/Mouse.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Engine;

namespace TestEngine
{
  TEST_CLASS(TestMouse)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_SetButtonDown_NoError)
    {
      // Just check we don't get a really bad error like a nullptr exception when using this function
      Mouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_SetButtonUp_NoError)
    {
      // Just check we don't get a really bad error like a nullptr exception when using this function
      Mouse mouse;
      mouse.setButtonUp(Mouse::kLeft);
      mouse.setButtonUp(Mouse::kRight);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_IsButtonDown)
    {
      Mouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      Assert::IsTrue(mouse.isButtonDown(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonDown(Mouse::kRight));

      Assert::IsFalse(mouse.isButtonDown(Mouse::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_IsButtonPressed)
    {
      Mouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      Assert::IsTrue(mouse.isButtonPressed(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonPressed(Mouse::kRight));

      Assert::IsFalse(mouse.isButtonPressed(Mouse::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_Flush)
    {
      Mouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      // Sanity check
      Assert::IsTrue(mouse.isButtonPressed(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonPressed(Mouse::kRight));
      Assert::IsTrue(mouse.isButtonDown(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonDown(Mouse::kRight));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Mouse_Update)
    {
      Mouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonUp(Mouse::kRight);

      Assert::IsTrue(mouse.isButtonPressed(Mouse::kLeft));
      Assert::IsFalse(mouse.isButtonPressed(Mouse::kRight));
      Assert::IsTrue(mouse.isButtonDown(Mouse::kLeft));
      Assert::IsFalse(mouse.isButtonDown(Mouse::kRight));

      mouse.update(0);

      mouse.setButtonUp(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      Assert::IsFalse(mouse.isButtonPressed(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonPressed(Mouse::kRight));
      Assert::IsFalse(mouse.isButtonDown(Mouse::kLeft));
      Assert::IsTrue(mouse.isButtonDown(Mouse::kRight));
    }
  };
}
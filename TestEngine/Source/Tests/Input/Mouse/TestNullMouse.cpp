#include "stdafx.h"

#include "Input/Mouse/NullMouse.h"

using namespace Engine;

namespace TestEngine
{
  TEST_CLASS(TestNullMouse)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_NullMouse_IsButtonDown)
    {
      NullMouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      Assert::IsFalse(mouse.isButtonDown(Mouse::kLeft));
      Assert::IsFalse(mouse.isButtonDown(Mouse::kRight));
      Assert::IsFalse(mouse.isButtonDown(Mouse::kMiddle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_NullMouse_IsButtonPressed)
    {
      NullMouse mouse;
      mouse.setButtonDown(Mouse::kLeft);
      mouse.setButtonDown(Mouse::kRight);

      Assert::IsFalse(mouse.isButtonPressed(Mouse::kLeft));
      Assert::IsFalse(mouse.isButtonPressed(Mouse::kRight));
      Assert::IsFalse(mouse.isButtonPressed(Mouse::kMiddle));
    }
  };
}
#include "stdafx.h"

#include "OpenGL/OpenGLWindow.h"

using namespace Engine;

namespace TestEngine
{

  TEST_CLASS(TestOpenGLWindow), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_OpenGLWindow_DefaultConstructor)
    {
      // This should just create a window using the current device primary monitor resolution
      // Check this doesn't cause any errors
      OpenGLWindow window;
      Assert::IsNotNull(window.getGLWindow());

      const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
      Assert::AreEqual(mode->width, window.getWidth());
      Assert::AreEqual(mode->height, window.getHeight());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_OpenGLWindow_CustomConstructor)
    {
      // This should just create a window using the inputted resolution
      // Check this doesn't cause any errors
      OpenGLWindow window(800, 600);
      Assert::IsNotNull(window.getGLWindow());

      Assert::AreEqual(800, window.getWidth());
      Assert::AreEqual(600, window.getHeight());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_OpenGLWindow_FullScreenConstructor)
    {
      OpenGLWindow window(OpenGLWindow::kFullScreen);
      Assert::IsTrue(window.isFullScreen());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_OpenGLWindow_SetScreenMode)
    {
      OpenGLWindow window;

      // Sanity check - by default it is created windowed
      Assert::IsFalse(window.isFullScreen());
      
      window.setScreenMode(OpenGLWindow::kFullScreen);
      Assert::IsTrue(window.isFullScreen());

      window.setScreenMode(OpenGLWindow::kWindowed);
      Assert::IsFalse(window.isFullScreen());
    }
  };
}
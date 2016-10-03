#include "stdafx.h"

#include "Time/Clock.h"

using namespace Engine;

uint64_t Clock::s_cyclesPerSecond = 2;
uint64_t cyclesPerSecond = 0;

namespace TestEngine
{

  TEST_CLASS(TestClock)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestClock_Setup)
    {
      // Set up glfw so we can get the timer frequency
      glfwInit();
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

      cyclesPerSecond = glfwGetTimerFrequency();
      Clock::init();
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestClock_Cleanup)
    {
      glfwTerminate();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Constructor)
    {
      Clock clock(10, 20);

      Assert::AreEqual(10, clock.getTargetFramesPerSecond());
      Assert::AreEqual((uint64_t)(20 * cyclesPerSecond), clock.getElapsedCycles());
      Assert::IsFalse(clock.getPaused());
      Assert::AreEqual(1.0f, clock.getTimeScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_CyclesToSeconds)
    {
      Assert::AreEqual(10.0f, Clock::cyclesToSeconds(20));
      Assert::AreEqual(0.0f, Clock::cyclesToSeconds(0));
      Assert::AreNotEqual(-10.0f, Clock::cyclesToSeconds(-20));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SecondsToCycles)
    {
      Assert::AreEqual((uint64_t)40, Clock::secondsToCycles(20));
      Assert::AreEqual((uint64_t)0, Clock::secondsToCycles(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Update)
    {
      Clock clock;

      clock.update(1);
      Assert::AreEqual((uint64_t)cyclesPerSecond, clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)(5 * cyclesPerSecond), clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)(5 * cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateSlowerThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(0.5f);

      clock.update(1);
      Assert::AreEqual((uint64_t)(0.5f * cyclesPerSecond), clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)(2.5f * cyclesPerSecond), clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)(2.5f* cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateFasterThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(2.0f);

      clock.update(1);
      Assert::AreEqual((uint64_t)(2 * cyclesPerSecond), clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)(10 * cyclesPerSecond), clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)(10 * cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_NoUpdateWhenPaused)
    {
      Clock clock;
      clock.setPaused(true);

      clock.update(1);
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStep)
    {
      Clock clock(1);

      clock.singleStep();
      Assert::AreEqual((uint64_t)cyclesPerSecond, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(2 * cyclesPerSecond), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(3 * cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepSlowerThanNormalTimeScale)
    {
      // Bump up the cpu cycles a little for this test (it will be reset)
      Clock clock(4);
      clock.setTimeScale(0.5f);

      clock.singleStep();
      Assert::AreEqual((uint64_t)(0.125f * cyclesPerSecond), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(0.25f * cyclesPerSecond), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(0.375f * cyclesPerSecond), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(0.5f * cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepFasterThanNormalTimeScale)
    {
      Clock clock(4);
      clock.setTimeScale(2.0f);

      clock.singleStep();
      Assert::AreEqual((uint64_t)(0.5f * cyclesPerSecond), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)cyclesPerSecond, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(1.5f * cyclesPerSecond), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_NoSingleStepWhenPaused)
    {
      Clock clock(4);
      clock.setPaused(true);

      clock.singleStep();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Reset)
    {
      Clock clock;

      clock.update(4);
      Assert::AreEqual((uint64_t)(4 * cyclesPerSecond), clock.getElapsedCycles());

      clock.reset();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }
  };
}
#include "stdafx.h"

#include "Time/Clock.h"

#include <chrono>
#include <thread>

using namespace OpenGL;


namespace TestEngine
{

  TEST_CLASS(TestClock), public GLUnitTest
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Constructor)
    {
      Clock clock(10, 20);

      Assert::AreEqual(10, clock.getTargetFramesPerSecond());
      Assert::AreEqual((uint64_t)(20 * CLOCKS_PER_SEC), clock.getElapsedCycles());
      Assert::IsFalse(clock.getPaused());
      Assert::AreEqual(1.0f, clock.getTimeScale());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_CyclesToSeconds)
    {
      Assert::AreEqual(10.0f, Clock::cyclesToSeconds(10.0f * CLOCKS_PER_SEC));
      Assert::AreEqual(0.0f, Clock::cyclesToSeconds(0));
      Assert::AreNotEqual(-10.0f, Clock::cyclesToSeconds(-10.0f * CLOCKS_PER_SEC));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SecondsToCycles)
    {
      Assert::AreEqual((uint64_t)20 * CLOCKS_PER_SEC, Clock::secondsToCycles(20));
      Assert::AreEqual((uint64_t)0, Clock::secondsToCycles(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Update)
    {
      Clock clock;

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC), clock.getElapsedCycles(), 5);

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC), clock.getElapsedCycles(), 10); // Compound errors

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC), clock.getElapsedCycles(), 15); // Compound errors
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateSlowerThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(0.5f);

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 0.5f), clock.getElapsedCycles(), 1);

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 0.5f), clock.getElapsedCycles(), 2); // Compound errors

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 0.5f), clock.getElapsedCycles(), 3); // Compound errors
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateFasterThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(2.0f);

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 2), clock.getElapsedCycles(), 10);

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 2), clock.getElapsedCycles(), 20); // Compound errors

      clock.update();
      AssertExt::assertAreAlmostEqual((uint64_t)(glfwGetTime() * CLOCKS_PER_SEC * 2), clock.getElapsedCycles(), 30); // Compound errors
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_NoUpdateWhenPaused)
    {
      Clock clock;
      clock.setPaused(true);

      clock.update();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.update();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());

      clock.update();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStep)
    {
      Clock clock(1);

      clock.singleStep();
      Assert::AreEqual((uint64_t)CLOCKS_PER_SEC, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(2 * CLOCKS_PER_SEC), clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)(3 * CLOCKS_PER_SEC), clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepSlowerThanNormalTimeScale)
    {
      // Bump up the cpu cycles a little for this test (it will be reset)
      Clock clock(4);
      clock.setTimeScale(0.5f);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(0.125f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 2);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(0.25f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 4);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(0.375f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 6);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(0.5f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 8);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepFasterThanNormalTimeScale)
    {
      Clock clock(4);
      clock.setTimeScale(2.0f);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(0.5f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 2);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)CLOCKS_PER_SEC, clock.getElapsedCycles(), 4);

      clock.singleStep();
      AssertExt::assertAreAlmostEqual((uint64_t)(1.5f * CLOCKS_PER_SEC), clock.getElapsedCycles(), 6);
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

      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      clock.update();
      Assert::AreNotEqual((uint64_t)0, clock.getElapsedCycles());

      clock.reset();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }
  };
}
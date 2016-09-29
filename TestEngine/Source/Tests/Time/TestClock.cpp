#include "stdafx.h"

#include "Time/Clock.h"

using namespace Engine;

uint64_t Clock::s_cyclesPerSecond = 2;

namespace TestEngine
{

  TEST_CLASS(TestClock)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_INITIALIZE(TestClock_Setup)
    {
      // Init the clock with a non trivial cycles per second
      // Do test initialize rather than test class initialize because we do not know in which order the
      // static variables etc. will be resolved
      // We also wish to reset any changes made by tests to the clock
      Clock::init(2);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Constructor)
    {
      Clock clock(10, 20);

      Assert::AreEqual(10, clock.getTargetFramesPerSecond());
      Assert::AreEqual((uint64_t)40, clock.getElapsedCycles());
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
      Assert::AreEqual((uint64_t)2, clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)10, clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)10, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateSlowerThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(0.5f);

      clock.update(1);
      Assert::AreEqual((uint64_t)1, clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)5, clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)5, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_UpdateFasterThanNormalTimeScale)
    {
      Clock clock;
      clock.setTimeScale(2.0f);

      clock.update(1);
      Assert::AreEqual((uint64_t)4, clock.getElapsedCycles());

      clock.update(4);
      Assert::AreEqual((uint64_t)20, clock.getElapsedCycles());

      clock.update(0);
      Assert::AreEqual((uint64_t)20, clock.getElapsedCycles());
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
      Assert::AreEqual((uint64_t)2, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)4, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)6, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepSlowerThanNormalTimeScale)
    {
      // Bump up the cpu cycles a little for this test (it will be reset)
      Clock::init(20);
      Clock clock(4);
      clock.setTimeScale(0.5f);

      clock.singleStep();
      Assert::AreEqual((uint64_t)2, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)4, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)6, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)8, clock.getElapsedCycles());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_SingleStepFasterThanNormalTimeScale)
    {
      Clock clock(4);
      clock.setTimeScale(2.0f);

      clock.singleStep();
      Assert::AreEqual((uint64_t)1, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)2, clock.getElapsedCycles());

      clock.singleStep();
      Assert::AreEqual((uint64_t)3, clock.getElapsedCycles());
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
    TEST_METHOD(Test_Clock_CalculateDeltaSeconds)
    {
      Clock clock1, clock2(DEFAULT_TARGET_FPS, 1);

      Assert::AreEqual(1.0f, clock2.calculateDeltaSeconds(clock1));

      clock1.update(1);
      Assert::AreEqual(0.0f, clock2.calculateDeltaSeconds(clock1));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_CalculateDeltaSeconds_ReflexivityWhenEqual)
    {
      Clock clock1, clock2;

      Assert::AreEqual(0.0f, clock2.calculateDeltaSeconds(clock1));
      Assert::AreEqual(0.0f, clock1.calculateDeltaSeconds(clock2));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Reset)
    {
      Clock clock;

      clock.update(4);
      Assert::AreEqual((uint64_t)8, clock.getElapsedCycles());

      clock.reset();
      Assert::AreEqual((uint64_t)0, clock.getElapsedCycles());
    }
  };
}
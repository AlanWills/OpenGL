#include "stdafx.h"

#include "Time/Clock.h"

using namespace Engine;

namespace TestEngine
{
  TEST_CLASS(TestClock)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Clock_Constructor)
    {
      // Non trivial cycles per second
      Clock::init(2);
      Clock clock(10, 10);

      TestUtils::assertAreAlmostEqual(10, clock.getTargetFramesPerSecond());
      Assert::AreEqual((uint64_t)20, clock.getElapsedCycles());
    }
  };
}
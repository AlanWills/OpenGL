#include "stdafx.h"

#include "Testing/TestUtils.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  void TestUtils::assertAreAlmostEqual(float expected, float actual, float epsilon)
  {
    Assert::IsTrue(abs(expected - actual) < epsilon);
  }
}
#include "stdafx.h"

#include "TestUtils.h"

namespace TestKernel
{
  //------------------------------------------------------------------------------------------------
  void TestUtils::assertAreAlmostEqual(float expected, float actual, float epsilon)
  {
    Assert::IsTrue(abs(expected - actual) <= epsilon);
  }
}
#include "stdafx.h"

#include "AssertExt.h"

namespace TestUtils
{
  //------------------------------------------------------------------------------------------------
  void AssertExt::assertAreAlmostEqual(float expected, float actual, float epsilon)
  {
    Assert::IsTrue(abs(expected - actual) <= epsilon);
  }
}
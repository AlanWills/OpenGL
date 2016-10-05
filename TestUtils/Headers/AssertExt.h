#pragma once

#include "DllExport.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestUtils
{

#define DEFAULT_FLOAT_EPSILON 0.0000001f

// A purely static class that provides extensions to the Microsoft Cpp unit testing framework
class DllExport AssertExt
{
public:
  /// \brief Check whether the two inputted float values differ by less than or equal to the inputted epsilon
  /// Asserts if expected and actual are more than epsilon apart
  static void assertAreAlmostEqual(float expected, float actual, float epsilon = DEFAULT_FLOAT_EPSILON);

private:
  // Set up the appropriate constructors and assignment operators so that an instance of this class is impossible to create
  AssertExt() = default;
  AssertExt(const AssertExt& testUtils) = delete;
  AssertExt& operator=(const AssertExt&) = delete;
};

}
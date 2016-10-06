#pragma once

#include "DllExport.h"
#include "CppUnitTest.h"

#include <vector>

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

  /// \brief Checks each element in turn to see if they satisfy the Assert::AreEqual condition
  /// Will also fail if the vectors are not the same length
  template <typename T>
  static void assertVectorContentsEqual(const std::vector<T>& expected, const std::vector<T>& actual);

  /// \brief Checks that the file with the inputted filepath exists
  static void assertFileExists(const std::string& fullFilePath);

  /// \brief Checks that the contents of the file with the inputted filepath matches the inputted expected string
  static void assertFileContents(const std::string& fullFilePath, const std::string& expectedFileContents);

private:
  // Set up the appropriate constructors and assignment operators so that an instance of this class is impossible to create
  AssertExt() = default;
  AssertExt(const AssertExt& testUtils) = delete;
  AssertExt& operator=(const AssertExt&) = delete;
};

//------------------------------------------------------------------------------------------------
template <typename T>
void AssertExt::assertVectorContentsEqual(const std::vector<T>& expected, const std::vector<T>& actual)
{
  Assert::AreEqual(expected.size(), actual.size());

  for (size_t i = 0, n = expected.size(); i < n; ++i)
  {
    Assert::AreEqual(expected[i], actual[i]);
  }
}

}
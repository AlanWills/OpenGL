#include "stdafx.h"

#include "AssertExt.h"

#include <fstream>

namespace TestUtils
{
  //------------------------------------------------------------------------------------------------
  void AssertExt::assertAreAlmostEqual(float expected, float actual, float epsilon)
  {
    float diff = abs(expected - actual);
    Assert::IsTrue(abs(expected - actual) <= epsilon);
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::assertFileExists(const std::string& fullFilePath)
  {
    std::fstream file(fullFilePath);
    Assert::IsTrue(file.good());
  }

  //------------------------------------------------------------------------------------------------
  void AssertExt::assertFileContents(const std::string& fullFilePath, const std::string& expectedFileContents)
  {
    assertFileExists(fullFilePath);

    std::ifstream file(fullFilePath);
    std::string actual, buffer;

    while (std::getline(file, buffer))
    {
      actual.append(buffer);
      actual.append("\n");
    }

    // Remove the final new line if it exists
    if ((actual.length() > 0) && (actual.back() == '\n'))
    {
      actual.pop_back();
    }

    Assert::AreEqual(expectedFileContents, actual);
  }
}
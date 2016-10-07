#include "stdafx.h"

#include "FileSystem/Path.h"

#include <vector>

using namespace Kernel;

namespace TestKernel
{
  TEST_CLASS(TestDirectory)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CombinePaths_NeitherHaveDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test");
      Path::combine(actual, "Path");

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CombinePaths_FirstHasDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test");
      actual.push_back(PATH_DELIMITER);
      Path::combine(actual, "Path");

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CombinePaths_SecondHasDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test"), second;
      actual.push_back(PATH_DELIMITER);

      second.push_back(PATH_DELIMITER);
      second.append("Path");

      Path::combine(actual, second);

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CombinePaths_BothHaveDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test"), second;
      actual.push_back(PATH_DELIMITER);

      second.push_back(PATH_DELIMITER);
      second.append("Path");

      Path::combine(actual, second);

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }
  };
}
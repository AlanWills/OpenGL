#include "stdafx.h"

#include "FileSystem/Path.h"

#include <vector>

using namespace Kernel;

namespace TestKernel
{
  TEST_CLASS(TestPathStatic)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Static_CombinePaths_NeitherHaveDelimiter)
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
    TEST_METHOD(Test_Path_Static_CombinePaths_FirstHasDelimiter)
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
    TEST_METHOD(Test_Path_Static_CombinePaths_SecondHasDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test"), second;
      second.push_back(PATH_DELIMITER);
      second.append("Path");

      Path::combine(actual, second);

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Static_CombinePaths_BothHaveDelimiter)
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
    TEST_METHOD(Test_Path_Static_GetParentDirectory_File)
    {
      std::string actual, expected("Root"), path;
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory");

      path = expected;
      path.push_back(PATH_DELIMITER);
      path.append("File.txt");

      Path::getParentDirectory(path, actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Static_GetParentDirectory_Directory_NoDelimiterEnding)
    {
      std::string actual, expected("Root"), path;

      path = expected;
      path.push_back(PATH_DELIMITER);
      path.append("Directory");

      Path::getParentDirectory(path, actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Static_GetParentDirectory_Directory_DelimiterEnding)
    {
      std::string actual, expected("Root"), path;

      path = expected;
      path.push_back(PATH_DELIMITER);
      path.append("Directory");
      path.push_back(PATH_DELIMITER);

      Path::getParentDirectory(path, actual);

      Assert::AreEqual(expected, actual);
    }
  };
}
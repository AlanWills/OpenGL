#include "stdafx.h"

#include "FileSystem/Path.h"
#include "Debug.h"

#include <vector>

using namespace Kernel;

namespace TestKernel
{
  TEST_CLASS(TestPathInstance)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_Directory_AsString)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory");

      Path path(expected);

      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_File_AsString)
    {
      std::string expected("Root");
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory.txt");

      Path path(expected);

      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_NeitherHaveDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      Path path("Test");
      path.combine("Path");

      // Test neither has delim
      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_FirstHasDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test");
      actual.push_back(PATH_DELIMITER);

      Path path(actual);
      path.combine("Path");

      // Test neither has delim
      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_SecondHasDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string second;
      second.push_back(PATH_DELIMITER);
      second.append("Path");

      Path path("Test");
      path.combine(second);

      // Test neither has delim
      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_BothHaveDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test"), second;
      actual.push_back(PATH_DELIMITER);

      second.push_back(PATH_DELIMITER);
      second.append("Path");

      Path path(actual);
      path.combine(second);

      // Test neither has delim
      Assert::AreEqual(expected, path.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_FirstEmpty)
    {
      std::string expected("Test");
      Path actual("");
      actual.combine("Test");

      // Test this didn't crash with an empty string and just squelched the empty one
      Assert::AreEqual(expected, actual.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_SecondEmpty)
    {
      std::string expected("Test");

      Path actual("Test");
      actual.combine("");

      // Test this didn't crash with an empty string and just squelched the empty one
      Assert::AreEqual(expected, actual.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_CombinePaths_BothEmpty)
    {
      std::string expected;

      Path actual("");
      actual.combine("");

      // Test this didn't crash with an empty string and just squelched the empty one
      Assert::AreEqual(expected, actual.asString());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_GetParentDirectory_File)
    {
      std::string expected("Root"), actual;
      expected.push_back(PATH_DELIMITER);
      expected.append("Directory");

      Path path(expected, "File.txt");
      path.getParentDirectory(actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_GetParentDirectory_Directory_NoDelimiterEnding)
    {
      std::string expected("Root"), actual;

      Path path(expected, "Directory");
      path.getParentDirectory(actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Path_Instance_GetParentDirectory_Directory_DelimiterEnding)
    {
      // This is a bit of a niche test - if people are using Paths, it's unlikely (but possible) this can happen)
      std::string actual, expected("Root"), fullPath;

      fullPath = expected;
      fullPath.push_back(PATH_DELIMITER);
      fullPath.append("Directory");
      fullPath.push_back(PATH_DELIMITER);

      Path path(fullPath);
      path.getParentDirectory(actual);

      Assert::AreEqual(expected, actual);
    }
  };
}
#include "stdafx.h"

#include "FileSystem/Path.h"

#include <vector>

using namespace Kernel;

namespace TestKernel
{
  TEST_CLASS(TestPathInstance)
  {
  public:

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
#include "stdafx.h"

#include "FileSystem/Path.h"
#include "FileSystem/File.h"
#include "FileSystem/Directory.h"

#include <fstream>
#include <vector>

using namespace Kernel;

static std::string testFilePath = "";
static std::string parentDirectory = "";
static std::string testFileName = "TestFile.txt";

namespace TestKernel
{
  TEST_CLASS(TestFileStatic)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestFileStatic_Initialize)
    {
      Directory::getExecutingAppDirectory(parentDirectory);

      testFilePath = parentDirectory;
      testFilePath.push_back(PATH_DELIMITER);
      testFilePath.append(testFileName);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestFileStatic_MethodCleanup)
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_Exists)
    {
      std::remove(testFilePath.c_str());
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      std::ofstream file(testFilePath);
      file << "";
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_Append)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");
      File::append(testFilePath, expected);
      Assert::IsTrue(File::exists(testFilePath));

      checkTestFileContents(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_Remove)
    {
      // Write something just to create the file
      File::append(testFilePath, "");
      Assert::IsTrue(File::exists(testFilePath));

      File::remove(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));

      // Make sure that deleting a file that is already deleted does not cause any problems
      File::remove(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_Create)
    {
      File::remove(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      File::create(testFilePath);
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_CreateInDirectory)
    {
      std::string directory;
      Directory::getExecutingAppDirectory(directory);

      File::createInDirectory(directory, testFileName);
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_ReadFile)
    {
      std::string expected("This is a test string");
      File::append(testFilePath, expected);

      std::string actual;
      File::read(testFilePath, actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Static_ReadLines)
    {
      std::vector<std::string> expected = 
      {
        "This",
        "is",
        "a",
        "test"
      };

      for (const std::string& str : expected)
      {
        File::append(testFilePath, str);
      }

      std::vector<std::string> actual;
      File::readLines(testFilePath, actual);

      AssertExt::assertVectorContentsEqual<std::string>(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    void checkTestFileContents(const std::string& expected)
    {
      AssertExt::assertFileContents(testFilePath, expected);
    }
  };
}
#include "stdafx.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"

#include <fstream>
#include <vector>

using namespace Kernel;

static std::string testFilePath = "";

namespace TestKernel
{
  TEST_CLASS(TestFile)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestFile_Initialize)
    {
      Directory::getExecutingAppDirectory(testFilePath);
      testFilePath.push_back(PATH_DELIMITER);
      testFilePath.append("TestFile.txt");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestFile_MethodCleanup)
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CombinePaths_NeitherHaveDelimiter)
    {
      std::string expected("Test");
      expected.push_back(PATH_DELIMITER);
      expected.append("Path");

      std::string actual("Test");
      File::combinePaths(actual, "Path");

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
      File::combinePaths(actual, "Path");

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

      File::combinePaths(actual, second);

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

      File::combinePaths(actual, second);

      // Test neither has delim
      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Constructor)
    {
      File file(testFilePath);
      std::string expected("TestString");

      // Check the file exists
      {
        std::ofstream fStream(testFilePath);
        Assert::IsTrue(fStream.good());

        // Write something to the file
        fStream << expected;
        fStream.close();
      }

      // Now check that the contents of the file is preserved by the constructor
      {
        file = File(testFilePath);

        checkTestFileContents(expected);
      }

      // Now check that the contents of the file is cleared by the constructor
      {
        file = File(testFilePath, true);

        checkTestFileContents("");
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Exists)
    {
      std::remove(testFilePath.c_str());
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      std::ofstream file(testFilePath);
      file << "";
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Append_Static)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");
      File::appendToFile(testFilePath, expected);
      Assert::IsTrue(File::exists(testFilePath));

      checkTestFileContents(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Append_Instance)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");

      File file(testFilePath);
      Assert::IsTrue(File::exists(testFilePath));

      file.appendToFile(expected);

      checkTestFileContents(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_DeleteFile)
    {
      // Write something just to create the file
      File::appendToFile(testFilePath, "");
      Assert::IsTrue(File::exists(testFilePath));

      File::deleteFile(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));

      // Make sure that deleting a file that is already deleted does not cause any problems
      File::deleteFile(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CreateFile)
    {
      File::deleteFile(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      File::createFile(testFilePath);
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CreateFile_ClearsOnCreation)
    {
      std::string expected("TestString");

      // Write something just to create the file
      {
        File::createFile(testFilePath);
        Assert::IsTrue(File::exists(testFilePath));

        File::appendToFile(testFilePath, expected);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents(expected);
      }

      // Now recreate the file, but don't clear it and check the contents is the same
      {
        File::createFile(testFilePath, false);
        Assert::IsTrue(File::exists(testFilePath));

        File::appendToFile(testFilePath, expected);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents(expected);
      }

      // Now recreate the file, but clear it and check it is now empty
      {
        File::createFile(testFilePath);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents("");
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_ReadFile_Static)
    {
      std::string expected("This is a test string");
      File::appendToFile(testFilePath, expected);

      std::string actual;
      File::readFile(testFilePath, actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_ReadFile_Instance)
    {
      std::string expected("This is a test string");

      File file(testFilePath);
      file.appendToFile(expected);

      std::string actual;
      file.readFile(actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_ReadLines_Static)
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
        File::appendToFile(testFilePath, str);
      }

      std::vector<std::string> actual;
      File::readLines(testFilePath, actual);

      AssertExt::assertVectorContentsEqual<std::string>(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_ReadLines_Instance)
    {
      std::vector<std::string> expected =
      {
        "This",
        "is",
        "a",
        "test"
      };

      File file(testFilePath);

      for (const std::string& str : expected)
      {
        file.appendToFile(str);
      }

      std::vector<std::string> actual;
      file.readLines(actual);

      AssertExt::assertVectorContentsEqual<std::string>(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    void checkTestFileContents(const std::string& expected)
    {
      AssertExt::assertFileContents(testFilePath, expected);
    }
  };
}
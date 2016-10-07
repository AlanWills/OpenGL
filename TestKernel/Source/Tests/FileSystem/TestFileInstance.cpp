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
  TEST_CLASS(TestFileInstance)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestFileInstance_Initialize)
    {
      Directory::getExecutingAppDirectory(parentDirectory);

      testFilePath = parentDirectory;
      testFilePath.push_back(PATH_DELIMITER);
      testFilePath.append(testFileName);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestFileInstance_MethodCleanup)
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_Constructor_FullPath)
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
    TEST_METHOD(Test_File_Constructor_Instance_RelativeToDirectory)
    {
      File file(parentDirectory, testFileName);
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
    TEST_METHOD(Test_File_Instance_Exists)
    {
      File file(testFilePath);

      std::remove(testFilePath.c_str());
      Assert::IsFalse(file.exists());

      // Write something just to create the file
      std::ofstream fileStream(testFilePath);
      fileStream << "";
      Assert::IsTrue(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_Append)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");

      File file(testFilePath);
      Assert::IsTrue(File::exists(testFilePath));

      file.append(expected);

      checkTestFileContents(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_Remove)
    {
      File file(testFilePath);

      // Write something just to create the file
      file.append("");
      Assert::IsTrue(file.exists());

      file.remove();
      Assert::IsFalse(file.exists());

      // Make sure that deleting a file that is already deleted does not cause any problems
      file.remove();
      Assert::IsFalse(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_Create)
    {
      File file(testFilePath);

      file.remove();
      Assert::IsFalse(file.exists());

      file.create();
      Assert::IsTrue(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_CreateFile_ClearsOnCreation)
    {
      std::string expected("TestString");

      // Write something just to create the file
      {
        File::create(testFilePath);
        Assert::IsTrue(File::exists(testFilePath));

        File::append(testFilePath, expected);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents(expected);
      }

      // Now recreate the file, but don't clear it and check the contents is the same
      {
        File::create(testFilePath, false);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents(expected);
      }

      // Now recreate the file, but clear it and check it is now empty
      {
        File::create(testFilePath);
        Assert::IsTrue(File::exists(testFilePath));

        checkTestFileContents("");
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_ReadFile)
    {
      std::string expected("This is a test string");

      File file(testFilePath);
      file.append(expected);

      std::string actual;
      file.read(actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Instance_ReadLines)
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
        file.append(str);
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
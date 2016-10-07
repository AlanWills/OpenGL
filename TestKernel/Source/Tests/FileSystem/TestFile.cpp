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
  TEST_CLASS(TestFile)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestFile_Initialize)
    {
      Directory::getExecutingAppDirectory(parentDirectory);

      testFilePath = parentDirectory;
      testFilePath.push_back(PATH_DELIMITER);
      testFilePath.append(testFileName);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD_CLEANUP(TestFile_MethodCleanup)
    {
      // Remove our test file so that we have a fresh file for each test
      std::remove(testFilePath.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Constructor_FullPath)
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
    TEST_METHOD(Test_File_Constructor_RelativeToDirectory)
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
    TEST_METHOD(Test_File_Exists_Static)
    {
      std::remove(testFilePath.c_str());
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      std::ofstream file(testFilePath);
      file << "";
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Exists_Instance)
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
    TEST_METHOD(Test_File_Append_Static)
    {
      // Write one word so we do not have to do any complex manual retrieval
      std::string expected("TestString");
      File::append(testFilePath, expected);
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

      file.append(expected);

      checkTestFileContents(expected);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Remove_Static)
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
    TEST_METHOD(Test_File_Remove_Instance)
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
    TEST_METHOD(Test_File_Create_Static)
    {
      File::remove(testFilePath);
      Assert::IsFalse(File::exists(testFilePath));

      // Write something just to create the file
      File::create(testFilePath);
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_Create_Instance)
    {
      File file(testFilePath);

      file.remove();
      Assert::IsFalse(file.exists());

      file.create();
      Assert::IsTrue(file.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CreateInDirectory_Static)
    {
      std::string directory;
      Directory::getExecutingAppDirectory(directory);

      File::createInDirectory(directory, testFileName);
      Assert::IsTrue(File::exists(testFilePath));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_CreateFile_ClearsOnCreation)
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
    TEST_METHOD(Test_File_ReadFile_Static)
    {
      std::string expected("This is a test string");
      File::append(testFilePath, expected);

      std::string actual;
      File::read(testFilePath, actual);

      Assert::AreEqual(expected, actual);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_File_ReadFile_Instance)
    {
      std::string expected("This is a test string");

      File file(testFilePath);
      file.append(expected);

      std::string actual;
      file.read(actual);

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
        File::append(testFilePath, str);
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
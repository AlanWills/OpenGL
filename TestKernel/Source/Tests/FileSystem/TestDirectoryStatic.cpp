#include "stdafx.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"

#include <vector>
#include <direct.h>

using namespace Kernel;

static std::string testDirectory = "";

namespace TestKernel
{
  TEST_CLASS(TestDirectoryStatic)
  {
  public:

    //------------------------------------------------------------------------------------------------
    // Can't have this as test method initialize because it doesn't seem to like creating the same folder over and over
    TEST_CLASS_INITIALIZE(TestDirectoryStatic_Initialize)
    {
      Directory::getExecutingAppDirectory(testDirectory);
      Path::combine(testDirectory, "TestDirectory");

      Assert::AreEqual(0, _mkdir(testDirectory.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestDirectoryStatic_Cleanup)
    {
      // Clean up the test directory
      Directory::remove(testDirectory);
      Assert::IsFalse(Directory::exists(testDirectory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_Exists)
    {
      Assert::IsTrue(Directory::exists(testDirectory));

      std::string nonExistentDirectory(testDirectory + "NonExistent");
      Assert::IsFalse(Directory::exists(nonExistentDirectory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_GetFiles_AllFilesInDirectoryOnly)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.txt");

      File file2(testDirectory, filename2);
      Assert::IsTrue(file2.exists());

      std::vector<std::string> actualFiles, expectedFiles =
      {
        testDirectory + PATH_DELIMITER + filename1,
        testDirectory + PATH_DELIMITER + filename2
      };

      Directory::getFiles(testDirectory, actualFiles);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_GetFiles_AllFilesInSubDirectoriesToo)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.txt");
      File file2(testDirectory, filename2);
      Assert::IsTrue(file2.exists());

      std::string nestedDir(testDirectory);
      Path::combine(nestedDir, "NestedDirectory");
      Directory::create(nestedDir);

      std::string filename3("TestFile3.txt");
      File file3(nestedDir, filename3);
      Assert::IsTrue(file3.exists());

      std::vector<std::string> actualFiles, expectedFiles =
      {
        nestedDir + PATH_DELIMITER + filename3,
        testDirectory + PATH_DELIMITER + filename1,
        testDirectory + PATH_DELIMITER + filename2,
      };

      Directory::getFiles(testDirectory, actualFiles, ".", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_GetDirectories_AllDirectoriesInDirectoryOnly)
    {
      //Assert::Fail();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_Remove)
    {
      std::string directory(testDirectory);
      directory.push_back(PATH_DELIMITER);
      directory.append("TestRemove");

      Assert::IsFalse(Directory::exists(directory));
      Assert::AreEqual(0, _mkdir(directory.c_str()));

      Assert::IsTrue(Directory::exists(directory));
      Directory::remove(directory);

      Assert::IsFalse(Directory::exists(directory));

      // Now try to remove it again to see we do not get any errors
      Directory::remove(directory);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_Create)
    {
      std::string directory(testDirectory);
      directory.push_back(PATH_DELIMITER);
      directory.append("TestCreate");

      Assert::IsFalse(Directory::exists(directory));
      Directory::create(directory);

      Assert::IsTrue(Directory::exists(directory));

      // Now try creating it again
      Directory::create(directory);

      // Cleanup
      Directory::remove(directory);
      Assert::IsFalse(Directory::exists(directory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_CreateParentToo)
    {
      std::string directory, parentDirectory(testDirectory);
      parentDirectory.push_back(PATH_DELIMITER);
      parentDirectory.append("TestCreate");

      directory = parentDirectory;
      directory.push_back(PATH_DELIMITER);
      directory.append("TestNested");

      Assert::IsFalse(Directory::exists(parentDirectory));
      Assert::IsFalse(Directory::exists(directory));
      Directory::create(directory);

      Assert::IsTrue(Directory::exists(parentDirectory));
      Assert::IsTrue(Directory::exists(directory));

      // Now try creating it again
      Directory::create(directory);

      // Cleanup
      Directory::remove(directory);
      Assert::IsFalse(Directory::exists(directory));

      Directory::remove(parentDirectory);
      Assert::IsFalse(Directory::exists(parentDirectory));
    }
  };
}
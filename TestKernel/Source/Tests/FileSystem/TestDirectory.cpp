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
  TEST_CLASS(TestDirectory)
  {
  public:

    //------------------------------------------------------------------------------------------------
    // Can't have this as test method initialize because it doesn't seem to like creating the same folder over and over
    TEST_CLASS_INITIALIZE(TestDirectory_Initialize)
    {
      Directory::getExecutingAppDirectory(testDirectory);
      Path::combine(testDirectory, "TestDirectory");

      Assert::AreEqual(0, _mkdir(testDirectory.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestDirectory_Cleanup)
    {
      // Clean up the test directory
      Directory::remove(testDirectory);
      Assert::IsFalse(Directory::exists(testDirectory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Exists)
    {
      Assert::IsTrue(Directory::exists(testDirectory));

      std::string nonExistentDirectory(testDirectory + "NonExistent");
      Assert::IsFalse(Directory::exists(nonExistentDirectory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_GetFiles_AllFilesInDirectoryOnly)
    {
      // Create some files
      std::string filename("TestFile1.txt");
      File file(testDirectory, filename);
      Assert::IsTrue(file.exists());

      std::vector<std::string> actualFiles, expectedFiles =
      {
        testDirectory + PATH_DELIMITER + "TestFile1.txt"
      };

      Directory::getFiles(testDirectory, actualFiles);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_GetDirectories_AllDirectoriesInDirectoryOnly)
    {
      
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Remove)
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
    TEST_METHOD(Test_Directory_Create)
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
    TEST_METHOD(Test_Directory_CreateParentToo)
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
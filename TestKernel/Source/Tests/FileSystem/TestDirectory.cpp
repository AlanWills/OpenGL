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
      Assert::AreEqual(0, _rmdir(testDirectory.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Exists)
    {
      Assert::IsTrue(Directory::exists(testDirectory));

      std::string nonExistentDirectory(testDirectory + "NonExistent");
      Assert::IsFalse(Directory::exists(nonExistentDirectory));
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
      std::string directory(testDirectory);
      directory.push_back(PATH_DELIMITER);
      directory.append("TestCreate");
      directory.push_back(PATH_DELIMITER);
      directory.append("TestNested");

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
    TEST_METHOD(Test_Directory_GetFiles_AllFilesInDirectoryOnly)
    {
      // Create some files
      File file("TestFile1.txt");
      file.createInDirectory(testDirectory);
      //Kernel::File::createInDirectory(testDirectory, "TestFile1.txt");

      std::vector<std::string> actualFiles, expectedFiles = 
      {
        "TestFile1.txt"
      };

      Directory::getFiles(testDirectory, actualFiles);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);
    }
  };
}
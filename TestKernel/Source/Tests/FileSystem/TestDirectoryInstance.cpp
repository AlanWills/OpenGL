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
  TEST_CLASS(TestDirectoryInstance)
  {
  public:

    //------------------------------------------------------------------------------------------------
    // Can't have this as test method initialize because it doesn't seem to like creating the same folder over and over
    TEST_CLASS_INITIALIZE(TestDirectoryInstance_Initialize)
    {
      Directory::getExecutingAppDirectory(testDirectory);
      Path::combine(testDirectory, "TestDirectory");

      DIR* testDir = opendir(testDirectory.c_str());

      if (!testDir)
      {
        // Create the test directory if necessary - be careful with the Static tests for Directory
        Assert::AreEqual(0, _mkdir(testDirectory.c_str()));
      }

      closedir(testDir);
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestDirectoryInstance_Cleanup)
    {
      // Clean up the test directory
      Directory::remove(testDirectory);
      Assert::IsFalse(Directory::exists(testDirectory));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Constructor_FullPath)
    {
      std::string dirPath(testDirectory);
      Path::combine(dirPath, "Test");

      Directory dir(dirPath);
      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Constructor_RelativePath)
    {
      std::string dirPath(testDirectory);
      Path::combine(dirPath, "Test");

      Directory dir(dirPath, "Test");
      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Exists)
    {
      Directory dir(testDirectory);
      Assert::IsTrue(dir.exists());

      std::string nonExistentDirPath(testDirectory + "NonExistent");
      Directory nonExistentDir(nonExistentDirPath);

      // Delete the directory created by Directory
      _rmdir(nonExistentDirPath.c_str());

      Assert::IsFalse(nonExistentDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetFiles_InDirectoryOnly)
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

      Directory dir(testDirectory);
      dir.getFiles(actualFiles);

      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetFiles_InDirectoryOnlyWithPattern)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.html");

      File file2(testDirectory, filename2);
      Assert::IsTrue(file2.exists());

      std::vector<std::string> actualFiles, expectedFiles =
      {
        testDirectory + PATH_DELIMITER + filename1,
      };

      Directory dir(testDirectory);
      dir.getFiles(actualFiles, ".txt");

      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetFiles_AllFiles)
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

      Directory dir(testDirectory);

      dir.getFiles(actualFiles, ".", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetFiles_AllFilesWithPattern)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.html");
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
      };

      Directory dir(testDirectory);

      dir.getFiles(actualFiles, ".txt", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetDirectories_InDirectoryOnly)
    {
      std::string enclosingDirectoryPath(testDirectory + "EnclosingDirectory");
      Directory enclosingDirectory(enclosingDirectoryPath);

      std::string directory1("TestDirectory1");
      Directory dir1(enclosingDirectoryPath, directory1);
      Assert::IsTrue(dir1.exists());

      std::string directory2("TestDirectory2");
      Directory dir2(enclosingDirectoryPath, directory2);
      Assert::IsTrue(dir2.exists());

      std::vector<std::string> actualDirectories, expectedDirectories =
      {
        enclosingDirectoryPath + PATH_DELIMITER + directory1,
        enclosingDirectoryPath + PATH_DELIMITER + directory2,
      };

      enclosingDirectory.getDirectories(actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      enclosingDirectory.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetDirectories_AllDirectories)
    {
      std::string enclosingDirectoryPath(testDirectory + "EnclosingDirectory");
      Directory enclosingDirectory(enclosingDirectoryPath);

      std::string directory1("TestDirectory1");
      Directory dir1(enclosingDirectoryPath, directory1);
      Assert::IsTrue(dir1.exists());

      std::string directory2("TestDirectory2");
      Directory dir2(enclosingDirectoryPath, directory2);
      Assert::IsTrue(dir2.exists());

      std::string nestedParent(enclosingDirectoryPath);
      Path::combine(nestedParent, directory2);

      std::string directory3("TestDirectory3");
      Directory dir3(nestedParent, directory3);
      Assert::IsTrue(dir3.exists());

      std::vector<std::string> actualDirectories, expectedDirectories =
      {
        enclosingDirectoryPath + PATH_DELIMITER + directory1,
        enclosingDirectoryPath + PATH_DELIMITER + directory2,
        nestedParent + PATH_DELIMITER + directory3,
      };

      enclosingDirectory.getDirectories(actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      dir3.remove();
      enclosingDirectory.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Remove)
    {
      std::string directory("TestRemove");
      Directory dir(testDirectory, directory);

      Assert::IsTrue(dir.exists());
      dir.remove();

      Assert::IsFalse(dir.exists());

      // Now try to remove it again to see we do not get any errors
      dir.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Create)
    {
      std::string directory("TestCreate"), fullDirPath;
      Directory dir(testDirectory, directory);

      fullDirPath = testDirectory;
      Path::combine(fullDirPath, directory);

      // Have to remove the dir created by the constructor so we can run create
      Assert::AreEqual(0, _rmdir(fullDirPath.c_str()));

      Assert::IsFalse(dir.exists());
      dir.create();

      Assert::IsTrue(dir.exists());

      // Now try creating it again
      dir.create();

      // Cleanup
      dir.remove();
      Assert::IsFalse(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_CreateParentToo)
    {
      std::string directory("TestNested"), parentDirectory("TestCreate"), parentDirectoryFull(testDirectory);
      parentDirectoryFull.push_back(PATH_DELIMITER);
      parentDirectoryFull.append(parentDirectory);

      Directory dir(parentDirectoryFull, directory), parentDir(testDirectory, parentDirectory);

      Assert::IsTrue(parentDir.exists());
      Assert::IsTrue(dir.exists());

      // Safe cleanup - don't rely on recursive delete in Directory
      dir.remove();
      Assert::IsFalse(dir.exists());

      parentDir.remove();
      Assert::IsFalse(parentDir.exists());
    }
  };
}
#include "stdafx.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "Utils/StringUtils.h"

#include <vector>
#include <direct.h>

static std::string testDirectory = "";

namespace TestKernel
{
  TEST_CLASS(TestDirectoryInstance)
  {
  public:

    //------------------------------------------------------------------------------------------------
    template <typename T>
    T create(const std::string& fullPath)
    {
      T obj(fullPath);
      Assert::IsTrue(obj.exists());

      return obj;
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    T create(const std::string& parentPath, const std::string& relativePath)
    {
      T obj(parentPath, relativePath);
      Assert::IsTrue(obj.exists());

      return obj;
    }

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

      create<Directory>(dirPath);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Constructor_RelativePath)
    {
      create<Directory>(testDirectory, "Test");
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Constructor_Path)
    {
      Path path(testDirectory, "Test");
      Directory dir(path);

      Assert::IsTrue(dir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Constructor_Copy)
    {
      Path path(testDirectory, "Test");
      Directory dir(path);
      Assert::IsTrue(dir.exists());

      // Now remove the directory
      rmdir(path.as_string().c_str());
      Assert::IsFalse(dir.exists());

      Directory dirCopy(dir);

      // Check the directory still does not exist
      Assert::IsFalse(dirCopy.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_AssignmentOperator)
    {
      Path path(testDirectory, "Test");
      Directory dir(path);
      Assert::IsTrue(dir.exists());

      // Now remove the directory
      rmdir(path.as_string().c_str());
      Assert::IsFalse(dir.exists());

      Directory dirCopy = dir;

      // Check the directory still does not exist
      Assert::IsFalse(dirCopy.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_EqualityOperator)
    {
      Path path(testDirectory, "Test");
      Directory original(path), same(path), notSame(testDirectory, "NotTheSameDirectory");

      Assert::IsTrue(original == same);
      Assert::IsFalse(original == notSame);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Exists)
    {
      // Create and check the test directory
      create<Directory>(testDirectory);
      
      std::string nonExistentDirPath(testDirectory + "NonExistent");
      Directory nonExistentDir(nonExistentDirPath);

      // Delete the directory created by Directory
      _rmdir(nonExistentDirPath.c_str());

      // Check the directory we deleted doesn't exist
      Assert::IsFalse(nonExistentDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindFiles_InDirectoryOnly)
    {
      // Create some files
      File file1 = create<File>(testDirectory, "TestFile1.txt");
      File file2 = create<File>(testDirectory, "TestFile2.txt");

      std::vector<File> actualFiles, expectedFiles =
      {
        file1,
        file2
      };

      Directory dir(testDirectory);
      dir.findFiles(actualFiles);

      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindFiles_InDirectoryOnlyWithPattern)
    {
      // Create some files
      File file1 = create<File>(testDirectory, "TestFile1.txt");
      File file2 = create<File>(testDirectory, "TestFile2.html");

      std::vector<File> actualFiles, expectedFiles =
      {
        file1
      };

      Directory dir(testDirectory);
      dir.findFiles(actualFiles, ".txt");

      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindFiles_AllFiles)
    {
      // Create some files
      File file1 = create<File>(testDirectory, "TestFile1.txt");
      File file2 = create<File>(testDirectory, "TestFile2.txt");

      std::string nestedDir(testDirectory);
      Path::combine(nestedDir, "NestedDirectory");
      Directory::create(nestedDir);

      File file3 = create<File>(nestedDir, "TestFile3.txt");

      std::vector<File> actualFiles, expectedFiles =
      {
        file3,
        file1,
        file2
      };

      Directory dir = create<Directory>(testDirectory);
      dir.findFiles(actualFiles, ".", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindFiles_AllFilesWithPattern)
    {
      // Create some files
      File file1 = create<File>(testDirectory, "TestFile1.txt");
      File file2 = create<File>(testDirectory, "TestFile2.html");

      std::string nestedDir(testDirectory);
      Path::combine(nestedDir, "NestedDirectory");
      Directory::create(nestedDir);

      File file3 = create<File>(nestedDir, "TestFile3.txt");

      std::vector<File> actualFiles, expectedFiles =
      {
        file3,
        file1,
      };

      Directory dir = create<Directory>(testDirectory);
      dir.findFiles(actualFiles, ".txt", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindDirectories_InDirectoryOnly)
    {
      std::string enclosingDirectoryPath(testDirectory + "EnclosingDirectory");
      Directory enclosingDirectory = create<Directory>(enclosingDirectoryPath);

      Directory dir1 = create<Directory>(enclosingDirectoryPath, "TestDirectory1");
      Directory dir2 = create<Directory>(enclosingDirectoryPath, "TestDirectory2");

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        dir1,
        dir2
      };

      enclosingDirectory.findDirectories(actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      enclosingDirectory.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_FindDirectories_AllDirectories)
    {
      std::string enclosingDirectoryPath(testDirectory + "EnclosingDirectory");
      Directory enclosingDirectory = create<Directory>(enclosingDirectoryPath);

      Directory dir1 = create<Directory>(enclosingDirectoryPath, "TestDirectory1");
      Directory dir2 = create<Directory>(enclosingDirectoryPath, "TestDirectory2");

      std::string nestedParent(enclosingDirectoryPath);
      Path::combine(nestedParent, "TestDirectory2");

      Directory dir3 = create<Directory>(nestedParent, "TestDirectory3");

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        dir1,
        dir2,
        dir3
      };

      enclosingDirectory.findDirectories(actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      dir1.remove();
      dir2.remove();
      dir3.remove();
      enclosingDirectory.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Remove)
    {
      Directory dir = create<Directory>(testDirectory, "TestRemove");
      dir.remove();

      Assert::IsFalse(dir.exists());

      // Now try to remove it again to see we do not get any errors
      dir.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_Create)
    {
      Directory dir = create<Directory>(testDirectory, "TestCreate");

      // Have to remove the dir created by the constructor so we can run create
      dir.remove();

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
      std::string parentDirectoryFull(testDirectory);
      parentDirectoryFull.push_back(PATH_DELIMITER);
      parentDirectoryFull.append("TestCreate");

      Directory dir = create<Directory>(parentDirectoryFull, "TestCreate");
      Directory parentDir = create<Directory>(testDirectory, "TestNested");

      // Safe cleanup - don't rely on recursive delete in Directory
      dir.remove();
      Assert::IsFalse(dir.exists());

      parentDir.remove();
      Assert::IsFalse(parentDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_CreateFile)
    {
      Directory dir(testDirectory);
      const File& createdDir = dir.createFile("Test.txt");
      Assert::IsTrue(createdDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_CreateDirectory)
    {
      Directory dir(testDirectory);
      const Directory& createdDir = dir.createDirectory("TestDirectory");
      Assert::IsTrue(createdDir.exists());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Instance_GetDirectoryName)
    {
      Directory dir(testDirectory);

      Assert::AreEqual("TestDirectory", dir.getDirectoryName().c_str());
    }
  };
}

//----------------------------------------------------------------------------------------------------------
namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {

      template<>
      static std::wstring ToString<Directory>(const Directory& directory)
      {
        const std::string& directoryPath = directory.getDirectoryPath();
        wchar_t buffer[1024];
        StringUtils::charToWchar(directoryPath.c_str(), buffer, 1024);

        return std::wstring(buffer);
      }

      template<>
      static std::wstring ToString<File>(const File& file)
      {
        const std::string& filePath = file.getFilePath();
        wchar_t buffer[1024];
        StringUtils::charToWchar(filePath.c_str(), buffer, 1024);

        return std::wstring(buffer);
      }
    }
  }
}
#include "stdafx.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "Utils/StringUtils.h"

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

      DIR* testDir = opendir(testDirectory.c_str());

      if (!testDir)
      {
        // Create the test directory if necessary - be careful with the Instance tests for Directory
        Assert::AreEqual(0, _mkdir(testDirectory.c_str()));
      }

      closedir(testDir);
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
    TEST_METHOD(Test_Directory_Static_FindFiles_InDirectoryOnly)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.txt");

      File file2(testDirectory, filename2);
      Assert::IsTrue(file2.exists());

      std::vector<File> actualFiles, expectedFiles =
      {
        testDirectory + PATH_DELIMITER + filename1,
        testDirectory + PATH_DELIMITER + filename2
      };

      Directory::findFiles(testDirectory, actualFiles);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_FindFiles_InDirectoryOnlyWithPattern)
    {
      // Create some files
      std::string filename1("TestFile1.txt");
      File file1(testDirectory, filename1);
      Assert::IsTrue(file1.exists());

      std::string filename2("TestFile2.html");

      File file2(testDirectory, filename2);
      Assert::IsTrue(file2.exists());

      std::vector<File> actualFiles, expectedFiles =
      {
        testDirectory + PATH_DELIMITER + filename1,
      };

      Directory::findFiles(testDirectory, actualFiles, ".txt");
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_FindFiles_AllFiles)
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

      std::vector<File> actualFiles, expectedFiles =
      {
        nestedDir + PATH_DELIMITER + filename3,
        testDirectory + PATH_DELIMITER + filename1,
        testDirectory + PATH_DELIMITER + filename2,
      };

      Directory::findFiles(testDirectory, actualFiles, ".", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_FindFiles_AllFilesWithPattern)
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

      std::vector<File> actualFiles, expectedFiles =
      {
        nestedDir + PATH_DELIMITER + filename3,
        testDirectory + PATH_DELIMITER + filename1,
      };

      Directory::findFiles(testDirectory, actualFiles, ".txt", true);
      AssertExt::assertVectorContentsEqual(expectedFiles, actualFiles);

      file1.remove();
      file2.remove();
      file3.remove();

      Assert::AreEqual(0, _rmdir(nestedDir.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_FindDirectories_InDirectoryOnly)
    {
      std::string enclosingDirectory(testDirectory);
      Path::combine(enclosingDirectory, "Enclosing");
      Directory::create(enclosingDirectory);
      Assert::IsTrue(Directory::exists(enclosingDirectory));

      std::string directory1("TestDirectory1"), directory1FullPath(enclosingDirectory);
      Path::combine(directory1FullPath, directory1);
      Directory::create(directory1FullPath);
      Assert::IsTrue(Directory::exists(directory1FullPath));

      std::string directory2("TestDirectory2"), directory2FullPath(enclosingDirectory);
      Path::combine(directory2FullPath, directory2);
      Directory::create(directory2FullPath);
      Assert::IsTrue(Directory::exists(directory2FullPath));

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        enclosingDirectory + PATH_DELIMITER + directory1,
        enclosingDirectory + PATH_DELIMITER + directory2,
      };

      Directory::findDirectories(enclosingDirectory, actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      Assert::AreEqual(0, _rmdir(directory1FullPath.c_str()));
      Assert::AreEqual(0, _rmdir(directory2FullPath.c_str()));
      Assert::AreEqual(0, _rmdir(enclosingDirectory.c_str()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_FindDirectories_AllDirectories)
    {
      std::string enclosingDirectory(testDirectory);
      Path::combine(enclosingDirectory, "Enclosing");
      Directory::create(enclosingDirectory);
      Assert::IsTrue(Directory::exists(enclosingDirectory));

      std::string directory1("TestDirectory1"), directory1FullPath(enclosingDirectory);
      Path::combine(directory1FullPath, directory1);
      Directory::create(directory1FullPath);
      Assert::IsTrue(Directory::exists(directory1FullPath));

      std::string directory2("TestDirectory2"), directory2FullPath(enclosingDirectory);
      Path::combine(directory2FullPath, directory2);
      Directory::create(directory2FullPath);
      Assert::IsTrue(Directory::exists(directory2FullPath));

      std::string nestedParent(enclosingDirectory);
      Path::combine(nestedParent, directory2);

      std::string directory3("TestDirectory3"), directory3FullPath(nestedParent);
      Path::combine(directory3FullPath, directory3);
      Directory::create(directory3FullPath);
      Assert::IsTrue(Directory::exists(directory3FullPath));

      std::vector<Directory> actualDirectories, expectedDirectories =
      {
        enclosingDirectory + PATH_DELIMITER + directory1,
        enclosingDirectory + PATH_DELIMITER + directory2,
        nestedParent + PATH_DELIMITER + directory3,
      };

      Directory::findDirectories(enclosingDirectory, actualDirectories);
      AssertExt::assertVectorContentsEqual(expectedDirectories, actualDirectories);

      Assert::AreEqual(0, _rmdir(directory1FullPath.c_str()));
      Assert::AreEqual(0, _rmdir(directory3FullPath.c_str()));
      Assert::AreEqual(0, _rmdir(directory2FullPath.c_str()));
      Assert::AreEqual(0, _rmdir(enclosingDirectory.c_str()));
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

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_Static_GetDirectoryName)
    {
      Assert::AreEqual("TestDirectory", Directory::getDirectoryName(testDirectory).c_str());
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
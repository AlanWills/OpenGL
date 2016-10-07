#include "stdafx.h"

#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"

#include <vector>

using namespace Kernel;

static std::string testDirectory = "";

namespace TestKernel
{
  TEST_CLASS(TestDirectory)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_INITIALIZE(TestDirectory_Initialize)
    {
      Directory::getExecutingAppDirectory(testDirectory);
      Path::combine(testDirectory, "TestDirectory");

      // Create some test files and directories
      std::string file(testDirectory);
      Path::combine(file, "TestFile1.txt");
      File::createFile(file);
    }

    //------------------------------------------------------------------------------------------------
    TEST_CLASS_CLEANUP(TestDirectory_Cleanup)
    {
      // TODO: Delete the test directory - add a function in directory
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_Directory_GetFiles_AllFilesInDirectoryOnly)
    {
      std::vector<std::string> actualFiles, expectedFiles = 
      {
        "TestFile1.txt"
      };

      Directory::getFiles(testDirectory, actualFiles);
    }
  };
}
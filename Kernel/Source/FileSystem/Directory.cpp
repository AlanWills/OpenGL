#include "Debug.h"
#include "FileSystem/Directory.h"
#include "FileSystem/Path.h"
#include "Utils/StringUtils.h"

#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void Directory::getExecutingAppDirectory(std::string& outputDir)
  {
    wchar_t w_buffer[1024];
    _wgetcwd(w_buffer, 1024);

    char c_buffer[1024];
    StringUtils::wcharToChar(w_buffer, c_buffer, 1024);
    outputDir.append(c_buffer);
  }

  //------------------------------------------------------------------------------------------------
  bool Directory::exists(const std::string& fullDirectoryPath)
  {
    DIR* result = opendir(fullDirectoryPath.c_str());
    bool exists = result != nullptr;

    closedir(result);

    return exists;
  }

  //------------------------------------------------------------------------------------------------
  void Directory::create(const std::string& directoryFullPath)
  {
    if (!exists(directoryFullPath))
    {
      std::string parentDirectory;
      Path::getParentDirectory(directoryFullPath, parentDirectory);

      if (!exists(parentDirectory))
      {
        // Recursively create all the parent directories
        create(parentDirectory);
      }

      int result = _mkdir(directoryFullPath.c_str());
      ASSERT(result == 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Directory::remove(const std::string& directoryFullPath)
  {
    if (exists(directoryFullPath))
    {


      int result = _rmdir(directoryFullPath.c_str());
      ASSERT(result == 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Directory::getFiles(const std::string& fullDirectoryPath,
    std::vector<std::string>& files,
    const std::string& extension,
    bool includeSubDirectories)
  {
    if (!exists(fullDirectoryPath))
    {
      ASSERT_FAIL_MSG("Directory does not exist");
      return;
    }

    DIR* dir = opendir(fullDirectoryPath.c_str());

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_REG)
      {
        std::string buffer(fullDirectoryPath);
        Path::combine(buffer, dirent->d_name);
        files.push_back(buffer);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  void Directory::getDirectories(
    const std::string& fullDirectoryPath,
    std::vector<std::string>& directories,
    bool includeSubDirectories)
  {
    if (!exists(fullDirectoryPath))
    {
      ASSERT_FAIL_MSG("Directory does not exist");
      return;
    }

    DIR* dir = opendir(fullDirectoryPath.c_str());

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_DIR)
      {

      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }
}
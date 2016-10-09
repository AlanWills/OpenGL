#include "DebugUtils/Debug.h"
#include "FileSystem/Directory.h"
#include "FileSystem/File.h"
#include "Utils/StringUtils.h"

#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  Directory::Directory(const std::string& fullDirectoryPath) :
    m_dirPath(fullDirectoryPath)
  {
    create(m_dirPath.asString());
  }

  //------------------------------------------------------------------------------------------------
  Directory::Directory(const std::string& parentDirectoryPath, const std::string& relativePathFromParent) :
    m_dirPath(parentDirectoryPath)
  {
    m_dirPath.combine(relativePathFromParent);
    create(m_dirPath.asString());
  }

  //------------------------------------------------------------------------------------------------
  Directory::Directory(const Path& path) :
    m_dirPath(path)
  {

  }

  //------------------------------------------------------------------------------------------------
  Directory::~Directory()
  {
  }

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
  std::string Directory::getExecutingAppDirectory()
  {
    std::string buffer;
    getExecutingAppDirectory(buffer);

    return buffer;
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
      std::vector<std::string> files;
      findFiles(directoryFullPath, files);

      for (const std::string& file : files)
      {
        File::remove(file);
      }

      std::vector<std::string> dirs;
      findDirectories(directoryFullPath, dirs);

      for (const std::string& dir : dirs)
      {
        Directory::remove(dir);
      }

      int result = _rmdir(directoryFullPath.c_str());
      ASSERT(result == 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findFiles(const std::string& fullDirectoryPath,
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

#ifdef WIN32
    // There are default folders (windows thing I guess).  Don't include these
    readdir(dir);
    readdir(dir);
#endif

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_REG)
      {
        std::string buffer(fullDirectoryPath);
        Path::combine(buffer, dirent->d_name);

        // Check the extension here
        if (extension != ".")
        {
          std::string thisExtension(dirent->d_name);
          thisExtension = thisExtension.substr(thisExtension.find_first_of('.'));

          if (extension == thisExtension)
          {
            files.push_back(buffer);
          }
        }
        else
        {
          files.push_back(buffer);
        }
      }
      else if (includeSubDirectories && dirent->d_type == DT_DIR)
      {
        std::string subDirPath(fullDirectoryPath);
        Path::combine(subDirPath, dirent->d_name);
        
        findFiles(subDirPath, files, extension, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findDirectories(
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

#ifdef WIN32
    // There are default folders (windows thing I guess).  Don't include these
    readdir(dir);
    readdir(dir);
#endif

    while (dirent* dirent = readdir(dir))
    {
      if (dirent->d_type == DT_DIR)
      {
        std::string buffer(fullDirectoryPath);
        Path::combine(buffer, dirent->d_name);
        directories.push_back(buffer);

        findDirectories(buffer, directories, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }
}
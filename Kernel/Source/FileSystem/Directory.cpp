#include "DebugUtils/Debug.h"
#include "FileSystem/Directory.h"
#include "Utils/StringUtils.h"

#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  Directory::Directory(const std::string& fullDirectoryPath) :
    m_dirPath(fullDirectoryPath)
  {
    create(m_dirPath.as_string());
  }

  //------------------------------------------------------------------------------------------------
  Directory::Directory(const std::string& parentDirectoryPath, const std::string& relativePathFromParent) :
    m_dirPath(parentDirectoryPath, parentDirectoryPath)
  {
    create(m_dirPath.as_string());
  }

  //------------------------------------------------------------------------------------------------
  Directory::Directory(const Path& path) :
    m_dirPath(path)
  {
    create(m_dirPath.as_string());
  }

  //------------------------------------------------------------------------------------------------
  Directory::Directory(const Directory& directory) :
    m_dirPath(directory.m_dirPath)
  {
    // No create here - preserve state of input directory
  }

  //------------------------------------------------------------------------------------------------
  Directory::~Directory()
  {
  }

  //------------------------------------------------------------------------------------------------
  Directory& Directory::operator=(const Directory& other)
  {
    // No create here - preserve state of input directory
    m_dirPath = other.m_dirPath;
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  void Directory::getExecutingAppDirectory(std::string& outputDir)
  {
    char buffer[1024];
    _getcwd(buffer, 1024);

    outputDir.append(buffer);
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
      std::vector<File> files;
      findFiles(directoryFullPath, files);

      for (const File& file : files)
      {
        file.remove();
      }

      std::vector<Directory> dirs;
      findDirectories(directoryFullPath, dirs);

      for (const Directory& dir : dirs)
      {
        dir.remove();
      }

      int result = _rmdir(directoryFullPath.c_str());
      ASSERT(result == 0);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findFiles(const std::string& fullDirectoryPath,
    std::vector<File>& files,
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
        Path filePath(fullDirectoryPath);
        filePath.combine(std::string(dirent->d_name));

        // Check the extension here
        if (extension != ".")
        {
          std::string thisExtension(dirent->d_name);
          thisExtension = thisExtension.substr(thisExtension.find_first_of('.'));

          if (extension == thisExtension)
          {
            files.emplace_back(File(filePath));
          }
        }
        else
        {
          files.push_back(File(filePath));
        }
      }
      else if (includeSubDirectories && dirent->d_type == DT_DIR)
      {
        Path subDirPath(fullDirectoryPath, std::string(dirent->d_name));
        findFiles(subDirPath.as_string(), files, extension, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  void Directory::findDirectories(
    const std::string& fullDirectoryPath,
    std::vector<Directory>& directories,
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
        Path dirBuffer(fullDirectoryPath);
        dirBuffer.combine(std::string(dirent->d_name));
        directories.push_back(dirBuffer);

        findDirectories(dirBuffer.as_string(), directories, includeSubDirectories);
      }
    }

    int result = closedir(dir);
    ASSERT(result == 0);
  }

  //------------------------------------------------------------------------------------------------
  File Directory::createFile(const std::string& fileName)
  {
    return File(m_dirPath.as_string(), fileName);
  }

  //------------------------------------------------------------------------------------------------
  Directory Directory::createDirectory(const std::string& directoryName)
  {
    return Directory(m_dirPath.as_string(), directoryName);
  }

  //------------------------------------------------------------------------------------------------
  std::string Directory::getDirectoryName(const std::string& directoryFullPath)
  {
    std::string directoryPath(directoryFullPath);

    if (directoryPath.back() == PATH_DELIMITER)
    {
      directoryPath.pop_back();
    }

    size_t position = directoryPath.find_last_of(PATH_DELIMITER);
    if (position != directoryPath.npos)
    {
      return directoryPath.substr(position + 1);
    }
    else
    {
      return "";
    }
  }
}
#pragma once

#include "DllExport.h"

#include <string>
#include <dirent.h>
#include <vector>

namespace Kernel
{

class DllExport Directory
{
  public:
    Directory(const std::string& fullDirectoryPath);
    Directory(const std::string& parentDirectoryPath, const std::string& relativePathFromParent);
    ~Directory();

    /// \brief Get the directory of the executing .exe
    static void getExecutingAppDirectory(std::string& outputDir);

    /// \brief Checks to see if a directory exists
    /// Returns true if it does
    static bool exists(const std::string& directoryFullPath);
    bool exists() const { return exists(m_dirPath); }

    /// \brief Creates a directory and any necessary parent directories if it does not already exist
    static void create(const std::string& directoryFullPath);
    void create() const { create(m_dirPath); }

    /// \brief Removes a directory and all of the contents inside it if it exists
    static void remove(const std::string& directoryFullPath);
    void remove() const { remove(m_dirPath); }

    /// \brief Obtain all of the files in the current directory and add them to the inputted vector
    /// Can provide a file extension filter to limit the files we are considering - by default considers all files
    /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
    static void getFiles(
      const std::string& fullDirectoryPath, 
      std::vector<std::string>& files, 
      const std::string& extension = ".", 
      bool includeSubDirectories = false);

    void getFiles(
      std::vector<std::string>& files,
      const std::string& extension = ".",
      bool includeSubDirectories = false) const 
    {
      getFiles(m_dirPath, files, extension, includeSubDirectories);
    }

    /// \brief Obtain all of the directories in the current directory and add them to the inputted vector
    /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
    static void getDirectories(
      const std::string& fullDirectoryPath,
      std::vector<std::string>& directories,
      bool includeSubDirectories = false);

    void getDirectories(
      std::vector<std::string>& directories,
      bool includeSubDirectories = false)
    {
      getDirectories(m_dirPath, directories, includeSubDirectories);
    }

  private:
    std::string m_dirPath;
};

};
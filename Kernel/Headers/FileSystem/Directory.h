#pragma once

#include "DllExport.h"
#include "File.h"

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
    Directory(const Path& path);
    ~Directory();

    /// Copy constructor and assignment operator do not create the directory; just copy the path
    /// This seems reasonable as we wish to preserve the internal state of the filesystem if we are copying a Directory which does not exist
    Directory(const Directory& directory);

    Directory& operator=(const Directory&);
    bool operator==(const Directory& rhs) const { return m_dirPath == rhs.m_dirPath; }

    /// \brief Get the directory of the executing .exe
    static void getExecutingAppDirectory(std::string& outputDir);
    static std::string getExecutingAppDirectory();

    /// \brief Checks to see if a directory exists
    /// Returns true if it does
    static bool exists(const std::string& directoryFullPath);
    bool exists() const { return exists(m_dirPath.as_string()); }

    /// \brief Creates a directory and any necessary parent directories if it does not already exist
    static void create(const std::string& directoryFullPath);
    void create() const { create(m_dirPath.as_string()); }

    /// \brief Removes a directory and all of the contents inside it if it exists
    static void remove(const std::string& directoryFullPath);
    void remove() const { remove(m_dirPath.as_string()); }

    /// \brief Obtain all of the files in the current directory and add them to the inputted vector
    /// Can provide a file extension filter to limit the files we are considering - by default considers all files
    /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
    static void findFiles(
      const std::string& fullDirectoryPath, 
      std::vector<File>& files, 
      const std::string& extension = ".", 
      bool includeSubDirectories = false);

    void findFiles(
      std::vector<File>& files,
      const std::string& extension = ".",
      bool includeSubDirectories = false) const 
    {
      findFiles(m_dirPath.as_string(), files, extension, includeSubDirectories);
    }

    /// \brief Obtain all of the directories in the current directory and add them to the inputted vector
    /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
    static void findDirectories(
      const std::string& fullDirectoryPath,
      std::vector<Directory>& directories,
      bool includeSubDirectories = false);

    void findDirectories(
      std::vector<Directory>& directories,
      bool includeSubDirectories = false)
    {
      findDirectories(m_dirPath.as_string(), directories, includeSubDirectories);
    }

    /// \brief Various creation functions for objects relative to this directory
    File createFile(const std::string& fileName);
    Directory createDirectory(const std::string& directoryName);

    /// \brief Returns the name of this directory relative to it's parent.  Contains no path delimiters
    static std::string getDirectoryName(const std::string& directoryFullPath);
    std::string getDirectoryName() const { return getDirectoryName(m_dirPath.as_string()); }

    const std::string& getDirectoryPath() const { return m_dirPath.as_string(); }

  private:
    Path m_dirPath;
};

};
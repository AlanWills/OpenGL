#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "Debug.h"

#include <fstream>
#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  File::File(const std::string& filePath, bool clearIfAlreadyExists) :
    m_filePath(filePath)
  {
    create(filePath, clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  File::File(const std::string& fullParentDirectoryPath, const std::string& relativeFilePath, bool clearIfAlreadyExists) :
    m_filePath(fullParentDirectoryPath)
  {
    Path::combine(m_filePath, relativeFilePath);
    create(m_filePath, clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  File::File(const Path& path) :
    File(path.asString())
  {
  }

  //------------------------------------------------------------------------------------------------
  File::~File()
  {
  }

  //------------------------------------------------------------------------------------------------
  bool File::exists(const std::string& fullFilePath)
  {
    struct stat buf;
    return stat(fullFilePath.c_str(), &buf) != -1;
  }

  //------------------------------------------------------------------------------------------------
  void File::append(const std::string& fullFilePath, const std::string& stringToAppend)
  {
    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath, std::ios_base::app);
    ASSERT(file.good());

    // Now append
    file << stringToAppend << std::endl;
  }

  //------------------------------------------------------------------------------------------------
  void File::create(const std::string& fullFilePath, bool clearIfAlreadyExists)
  {
    if (!clearIfAlreadyExists && exists(fullFilePath))
    {
      // If it exists already and we do not need to clear it, we are done
      return;
    }

    // Create the parent directory
    std::string parentDir;
    Path::getParentDirectory(fullFilePath, parentDir);
    Directory::create(parentDir);

    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath);
    if (clearIfAlreadyExists)
    {
      file.clear();
    }

    ASSERT(file.good());
  }

  //------------------------------------------------------------------------------------------------
  void File::createInDirectory(const std::string& directoryFullPath, const std::string& relativeFilePath, bool clearIfAlreadyExists)
  {
    std::string fullFilePath(directoryFullPath);
    Path::combine(fullFilePath, relativeFilePath);

    create(fullFilePath, clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  void File::remove(const std::string& fullFilePath)
  {
    std::remove(fullFilePath.c_str());
  }

  //------------------------------------------------------------------------------------------------
  void File::read(const std::string& fullFilePath, std::string& outFileContents)
  {
    std::ifstream file(fullFilePath);
    ASSERT(file.good());

    std::string buffer;

    while (std::getline(file, buffer))
    {
      outFileContents.append(buffer);
      outFileContents.append("\n");
    }

    // Remove the final \n
    outFileContents.pop_back();
  }

  //------------------------------------------------------------------------------------------------
  void File::readLines(const std::string& fullFilePath, std::vector<std::string>& outLines)
  {
    std::ifstream file(fullFilePath);
    ASSERT(file.good());

    std::string buffer;

    while (std::getline(file, buffer))
    {
      outLines.push_back(buffer);
    }
  }
}
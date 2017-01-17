#include "FileSystem/File.h"
#include "FileSystem/Directory.h"
#include "DebugUtils/Debug.h"

#include <fstream>
#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  File::File(const std::string& filePath, bool clearIfAlreadyExists) :
    m_filePath(filePath)
  {
    create(m_filePath.as_string(), clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  File::File(const std::string& fullParentDirectoryPath, const std::string& relativeFilePath, bool clearIfAlreadyExists) :
    m_filePath(fullParentDirectoryPath, relativeFilePath)
  {
    create(m_filePath.as_string(), clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  File::File(const Path& path, bool clearIfAlreadyExists) :
    m_filePath(path)
  {
    create(m_filePath.as_string(), clearIfAlreadyExists);
  }

  //------------------------------------------------------------------------------------------------
  File::File(const File& file) :
    m_filePath(file.m_filePath)
  {
    // No create here - preserve state of input file
  }

  //------------------------------------------------------------------------------------------------
  File::~File()
  {
  }

  //------------------------------------------------------------------------------------------------
  File& File::operator=(const File& other)
  {
    // No create here - preserve state of input directory
    m_filePath = other.m_filePath;
    return *this;
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
    create(Path(directoryFullPath, relativeFilePath).as_string(), clearIfAlreadyExists);
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
    ASSERT(!outFileContents.empty());
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

  //------------------------------------------------------------------------------------------------
  std::string File::getFileName() const
  {
    const std::string& filePath = m_filePath.as_string();

    if (filePath.empty())
    {
      ASSERT_FAIL();
      return "";
    }

    std::string fileName(filePath);
    size_t index = fileName.find_last_of(PATH_DELIMITER);

    if (index < fileName.npos)
    {
      return fileName.substr(index + 1);
    }
    else
    {
      return "";
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string File::getExtensionlessFileName(const std::string& filePath)
  {
    if (filePath.empty())
    {
      ASSERT_FAIL();
      return "";
    }

    size_t extIndex = filePath.find_last_of('.');   // Find last here in case we have a \\..\\ in our file path
    size_t delimIndex = filePath.find_last_of(PATH_DELIMITER);

    if (extIndex == filePath.npos &&
        delimIndex != filePath.npos)
    {
      return filePath.substr(delimIndex + 1, filePath.size());
    }
    else if (extIndex != filePath.npos &&
             delimIndex == filePath.npos)
    {
      return filePath.substr(0, extIndex);
    }
    else if (extIndex != filePath.npos &&
             delimIndex != filePath.npos)
    {
      return filePath.substr(delimIndex + 1, extIndex - (delimIndex + 1));
    }
    else
    {
      ASSERT_FAIL();
      return "";
    }
  }
}
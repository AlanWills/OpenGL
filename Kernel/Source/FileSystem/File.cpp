#include "FileSystem/File.h"
#include "Debug.h"

#include <fstream>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void File::combinePaths(std::string& firstPath, const std::string& secondPath)
  {
    // If the first path doesn't end in the delimiter and the second doesn't begin with the delimiter we should append the delimiter to the first path
    if ((firstPath.back() != PATH_DELIMITER) && (secondPath.front() != PATH_DELIMITER))
    {
      firstPath.push_back(PATH_DELIMITER);
    }
    // If the first path ends in the delimiter and the second beings with the delimiter we remove it from the end of the first path
    else if ((firstPath.back() == PATH_DELIMITER) && (secondPath.front() == PATH_DELIMITER))
    {
      firstPath.pop_back();
    }

    firstPath.append(secondPath);
  }

  //------------------------------------------------------------------------------------------------
  bool File::exists(const std::string& fullFilePath)
  {
    std::fstream file(fullFilePath);

    return file.good();
  }

  //------------------------------------------------------------------------------------------------
  void File::appendToFile(const std::string& fullFilePath, const std::string& stringToAppend)
  {
    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath, std::ios_base::app);
    ASSERT(file.good());

    // Now append
    file << stringToAppend << std::endl;
  }

  //------------------------------------------------------------------------------------------------
  void File::createFile(const std::string& fullFilePath, bool clearIfAlreadyExists)
  {
    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath);
    ASSERT(file.good());

    if (clearIfAlreadyExists)
    {
      file.clear();
    }

    // Write to file so it is created
    file << "";
  }

  //------------------------------------------------------------------------------------------------
  void File::deleteFile(const std::string& fullFilePath)
  {
    std::remove(fullFilePath.c_str());
  }

  //------------------------------------------------------------------------------------------------
  void File::readFile(const std::string& fullFilePath, std::string& outFileContents)
  {
    std::ifstream file(fullFilePath);
    ASSERT(file.good());

    std::string buffer;

    while (std::getline(file, buffer))
    {
      outFileContents.append(buffer);
    }
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
#include "FileSystem/File.h"
#include "Debug.h"

#include <fstream>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void File::combinePaths(std::string& firstPath, const std::string& secondPath)
  {
    firstPath.push_back(PATH_DELIMITER);
    firstPath.append(secondPath);
  }

  //------------------------------------------------------------------------------------------------
  void File::appendToFile(const std::string& fullFilePath, const std::string& stringToAppend)
  {
    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath);
    ASSERT(file.good());

    // Now append
    file << stringToAppend;
    file.close();
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

    file.close();
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

    file.close();
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

    file.close();
  }
}
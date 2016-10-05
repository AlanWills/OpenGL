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
  void File::createFile(const std::string& fullFilePath)
  {
    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath);
    ASSERT(file.good());

    file.close();
  }
}
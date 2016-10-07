#include "FileSystem/File.h"
#include "Debug.h"

#include <fstream>
#include <direct.h>

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  File::File(const std::string& fullFilePath, bool clearIfAlreadyExists) :
    m_fullFilePath(fullFilePath)
  {
    createFile(fullFilePath, clearIfAlreadyExists);
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
    if (!clearIfAlreadyExists && exists(fullFilePath))
    {
      // If it exists already and we do not need to clear it, we are done
      return;
    }

    // TODO: Create all the directories necessary too
    //ASSERT_FAIL_MSG("TODO");

    // Automatically creates the file if it does not exist
    std::ofstream file(fullFilePath);
    if (clearIfAlreadyExists)
    {
      file.clear();
    }

    ASSERT(file.good());
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
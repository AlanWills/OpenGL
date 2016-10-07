#include "FileSystem/Directory.h"
#include "Utils/StringUtils.h"

namespace Kernel
{
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
  void Directory::getFiles(const std::string& fullDirectoryPath,
    std::vector<std::string>& files,
    const std::string& extension,
    bool includeSubDirectories)
  {
    // TODO: Check directory exists

    DIR* dir = opendir(fullDirectoryPath.c_str());

    while (dirent* dirent = readdir(dir))
    {
      //if (dirent->d_type)
    }
  }
}
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
    /// \brief Get the directory of the executing .exe
    static void getExecutingAppDirectory(std::string& outputDir);

    /// \brief Obtain all of the files in the current directory and add them to the inputted vector
    /// Can provide a file extension filter to limit the files we are considering - by default considers all files
    /// Can provide a flag to search recursively through subdirectories too - by default will not search recursively
    static void getFiles(
      const std::string& fullDirectoryPath, 
      std::vector<std::string>& files, 
      const std::string& extension = ".", 
      bool includeSubDirectories = false);
};

};
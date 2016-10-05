#pragma once

#include "DllExport.h"

#include <string>

namespace Kernel
{

class DllExport Directory
{
  public:
    /// \brief Get the directory of the executing .exe
    static void getExecutingAppDirectory(std::string& outputDir);
};

};
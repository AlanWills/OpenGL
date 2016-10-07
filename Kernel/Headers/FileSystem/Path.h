#pragma once

#include "DllExport.h"

#include <string>

namespace Kernel
{

#ifdef WIN32
#define PATH_DELIMITER '\\'
#else
#define PATH_DELIMITER '/'
#endif

class DllExport Path
{
  public:
    /// \brief Appends a PATH_DELIMITER and the secondPath onto the firstPath
    /// std::string first("first\\path"), second("second\\path");
    /// e.g. combine(first, second) would change firstPath to "first\\path\\second\\path";
    static void combine(std::string& firstPath, const std::string& secondPath);
};

};
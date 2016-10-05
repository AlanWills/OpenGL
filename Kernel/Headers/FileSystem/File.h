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

class DllExport File
{
  public:
    /// \brief Appends a PATH_DELIMITER and the secondPath onto the firstPath
    /// std::string first("first\\path"), second("second\\path");
    /// e.g. combinePaths(first, second) would change firstPath to "first\\path\\second\\path";
    static void combinePaths(std::string& firstPath, const std::string& secondPath);

    /// \brief Opens a file and adds the inputted string to the end of it
    /// Will create the file if it does not exist
    static void appendToFile(const std::string& fullFilePath, const std::string& stringToAppend);

    /// \brief Creates a file if it does not exist.
    /// Does nothing if it does exist
    static void createFile(const std::string& fullFilePath);
};

};
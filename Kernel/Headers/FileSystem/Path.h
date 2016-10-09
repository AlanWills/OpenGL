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
    Path(const std::string& path);
    Path(const std::string& parentPath, const std::string& relativePath);
    ~Path();

    /// \brief Appends a PATH_DELIMITER and the secondPath onto the firstPath
    /// std::string first("first\\path"), second("second\\path");
    /// e.g. combine(first, second) would change firstPath to "first\\path\\second\\path";
    static void combine(std::string& firstPath, const std::string& secondPath);
    Path& combine(const std::string& secondPath) { combine(m_path, secondPath); return *this; }   // Return a reference to this so we can use builder pattern for combining

    /// \brief Returns the directory the object represented by the inputted path is in.
    /// e.g. for Root\\Directory\\File.txt this would return Root\\Directory
    /// e.g. for Root\\Directory this would return Root and for Root\\Directory\\ this would return Root
    /// Appends the full path onto the output string so anything already in the string will not be removed
    static void getParentDirectory(const std::string& fullPath, std::string& outParentDirectory);
    void getParentDirectory(std::string& outParentDirectory) const { getParentDirectory(m_path, outParentDirectory); }

    /// \brief Returns the path represented by this object as a string
    const std::string& asString() const { return m_path; }

  private:
    std::string m_path;
};

};
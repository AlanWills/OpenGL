#pragma once

#include "DllExport.h"

#include <string>
#include <stdarg.h>

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
    Path(const std::string& fullPath);

    template <typename... T>
    Path(const std::string& path, const T&... paths);

    Path(const Path& path);   // Copy constructor just copies underlying string
    ~Path();

    Path& operator=(const Path& other);
    bool operator==(const Path& rhs) const { return m_path == rhs.m_path; }

    /// \brief Appends a PATH_DELIMITER and the secondPath onto the firstPath
    /// std::string first("first\\path"), second("second\\path");
    /// e.g. combine(first, second) would change firstPath to "first\\path\\second\\path";
    template <typename T, typename... Args>
    void combine(const T& path, const Args&... args);

    void combine(const std::string& path);
    void combine(const char* path) { combine(std::string(path)); }


    /// \brief Returns the directory the object represented by the inputted path is in.
    /// e.g. for Root\\Directory\\File.txt this would return Root\\Directory
    /// e.g. for Root\\Directory this would return Root and for Root\\Directory\\ this would return Root
    /// Appends the full path onto the output string so anything already in the string will not be removed
    static void getParentDirectory(const std::string& fullPath, std::string& outParentDirectory);
    void getParentDirectory(std::string& outParentDirectory) const { getParentDirectory(m_path, outParentDirectory); }

    /// \brief Sets the stored string path to be the new inputted values
    /// Allows a way to reuse the same Path object rather than constructing a new one
    void reset(const char* path, ...);

    /// \brief Will remove the inputted path from this instance's path and return the value as a string
    /// Will fail and return "" if the inputted path is not an ancestor of this path.
    /// Leading delimiters will be trimmed
    std::string relativeTo(const Path& path) const;

    /// \brief Returns the path represented by this object as a string
    const std::string& as_string() const { return m_path; }

  private:
    void combine(va_list strings);

    std::string m_path;
};

//------------------------------------------------------------------------------------------------
template <typename... T>
Path::Path(const std::string& path, const T&... paths) :
  m_path(path)
{
  combine(paths...);
}

//------------------------------------------------------------------------------------------------
template <typename T, typename... Args>
void Path::combine(const T& path, const Args&... paths)
{
  combine(path);
  combine(paths...);
}

};
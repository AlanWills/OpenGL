#include "FileSystem/Path.h"
#include "DebugUtils/Debug.h"

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  Path::Path(const std::string& fullPath) :
    m_path(fullPath)
  {
    // Creating an empty path is a little odd
    ASSERT(!m_path.empty());
  }

  //------------------------------------------------------------------------------------------------
  Path::Path(const Path& path) :
    m_path(path.m_path)
  {
    // Creating an empty path is a little odd
    ASSERT(!m_path.empty());
  }

  //------------------------------------------------------------------------------------------------
  Path::~Path()
  {
  }

  //------------------------------------------------------------------------------------------------
  Path& Path::operator=(const Path& other)
  {
    m_path = other.m_path;
    return *this;
  }

  //------------------------------------------------------------------------------------------------
  void Path::reset(const char* path, ...)
  {
    m_path.clear();
    m_path.append(path);

    // Creating an empty path is a little odd
    ASSERT(path && path != "");

    va_list args;
    va_start(args, path);
    combine(args);
    va_end(args);
  }

  //------------------------------------------------------------------------------------------------
  void Path::combine(va_list paths)
  {
    while (*paths != '\0')
    {
      std::string secondPath(paths);
      combine(secondPath);
      ++paths;
    }
  }

  //------------------------------------------------------------------------------------------------
  void Path::combine(const std::string& path)
  {
    // If the first path doesn't end in the delimiter and the second doesn't start with the delimiter we should append the delimiter to the first path
    if ((m_path.back() != PATH_DELIMITER) && (path.front() != PATH_DELIMITER))
    {
      m_path.push_back(PATH_DELIMITER);
    }
    // If the first path ends in the delimiter and the second beings with the delimiter we remove it from the end of the first path
    else if ((m_path.back() == PATH_DELIMITER) && (path.front() == PATH_DELIMITER))
    {
      m_path.pop_back();
    }

    m_path.append(path);
  }

  //------------------------------------------------------------------------------------------------
  void Path::getParentDirectory(const std::string& fullPath, std::string& outParentDirectory)
  {
    // This can probably be done in a more efficient manner

    outParentDirectory.append(fullPath);

    if (outParentDirectory.back() == PATH_DELIMITER)
    {
      // If the path ends in a path delimiter, we do not want to count this so remove it
      outParentDirectory.pop_back();
    }

    size_t indexOfPathDelimiter = outParentDirectory.find_last_of(PATH_DELIMITER);
    while (outParentDirectory.length() > indexOfPathDelimiter)
    {
      outParentDirectory.pop_back();
    }
  }

  //------------------------------------------------------------------------------------------------
  std::string Path::relativeTo(const Path& parent) const
  {
    const std::string& parentStr = parent.as_string();
    std::string result(m_path.substr(parentStr.size() + 1));

    ASSERT(parentStr.size() < m_path.size());

    for (int i = 0; i < parentStr.size(); ++i)
    {
      if (parentStr[i] != m_path[i])
      {
        result = m_path.substr(i);
        break;
      }
    }

    if (result.front() == PATH_DELIMITER)
    {
      result = result.substr(1);
    }

    ASSERT(result.front() != PATH_DELIMITER);
    return result;
  }
}
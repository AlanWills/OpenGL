#include "FileSystem/Path.h"
#include "DebugUtils/Debug.h"

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  Path::Path(const std::string& path)
  {
    reset(path);
  }

  //------------------------------------------------------------------------------------------------
  Path::Path(const std::string& parentPath, const std::string& relativePath) :
    m_path(parentPath)
  {
    reset(parentPath, relativePath);
  }

  //------------------------------------------------------------------------------------------------
  Path::Path(const Path& path)
  {
    reset(path.asString());
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
  void Path::reset(const std::string& fullPath)
  {
    // Creating an empty path is a little odd
    ASSERT(!fullPath.empty());

    m_path = fullPath;
  }

  //------------------------------------------------------------------------------------------------
  void Path::reset(const std::string& parentPath, const std::string& relativePath)
  {
    // Creating an empty path is a little odd and calling this with an empty relative path is odd too (though still valid)
    ASSERT(!parentPath.empty() && !relativePath.empty());

    m_path = parentPath;
    combine(m_path, relativePath);
  }

  //------------------------------------------------------------------------------------------------
  void Path::combine(std::string& firstPath, const std::string& secondPath)
  {
    if (secondPath.empty())
    {
      // Check that the first path is not empty - if it is, this is a weird situation (although still valid)
      // Appending nothing to a non-empty path seems ok, but appending two empty paths is odd
      ASSERT(!firstPath.empty());
      return;
    }

    if (firstPath.empty())
    {
      // I don't feel like this is a good situation to be in - it is valid, but odd
      ASSERT_FAIL();
      firstPath.append(secondPath);
      return;
    }

    // If the first path doesn't end in the delimiter and the second doesn't begin with the delimiter we should append the delimiter to the first path
    if ((firstPath.back() != PATH_DELIMITER) && (secondPath.front() != PATH_DELIMITER))
    {
      firstPath.push_back(PATH_DELIMITER);
    }
    // If the first path ends in the delimiter and the second beings with the delimiter we remove it from the end of the first path
    else if ((firstPath.back() == PATH_DELIMITER) && (secondPath.front() == PATH_DELIMITER))
    {
      firstPath.pop_back();
    }

    firstPath.append(secondPath);
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
}
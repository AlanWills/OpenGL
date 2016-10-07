#include "FileSystem/Path.h"

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void Path::combine(std::string& firstPath, const std::string& secondPath)
  {
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
}
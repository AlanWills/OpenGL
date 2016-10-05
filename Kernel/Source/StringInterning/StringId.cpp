#include "StringInterning/StringId.h"

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  StringId internString(const char* str)
  {
    return stringToStringId(str);
  }
}
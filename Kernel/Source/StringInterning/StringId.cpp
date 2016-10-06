#include "StringInterning/StringId.h"
#include "Debug.h"

namespace Kernel
{
  static std::unordered_map<StringId, const char*> g_stringIdTable;
  // Maybe have a reverse map so we can look to see if the string exists before hashing?

  //------------------------------------------------------------------------------------------------
  StringId internString(const char* str)
  {
    StringId strId = stringToStringId(str);

    if (g_stringIdTable.find(strId) == g_stringIdTable.end())
    {
      // If our string does not exist in the lookup table, we should add it
      g_stringIdTable.emplace(strId, str);
    }

    return strId;
  }

  //------------------------------------------------------------------------------------------------
  const char* deinternString(StringId strId)
  {
    ASSERT(g_stringIdTable.find(strId) != g_stringIdTable.end());

    return g_stringIdTable[strId];
  }
}
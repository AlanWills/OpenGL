#include "StringInterning/StringId.h"
#include "Debug.h"

namespace Kernel
{
  static std::unordered_map<StringId, const char*> g_stringIdTable;
  static std::unordered_map<const char*, StringId> g_idStringTable;   // Used for quick interning

  //------------------------------------------------------------------------------------------------
  StringId internString(const char* str)
  {
    StringId strId = stringToStringId(str);

    if (g_stringIdTable.find(strId) == g_stringIdTable.end())
    {
      // If our string does not exist in the lookup table, we should add it
      g_stringIdTable.emplace(strId, str);

      // Add it to our reverse map too
      g_idStringTable.emplace(str, strId);
    }

    return strId;
  }

  //------------------------------------------------------------------------------------------------
  StringId internStringFast(const char* str)
  {
    ASSERT(g_idStringTable.find(str) != g_idStringTable.end());
    return g_idStringTable[str];
  }

  //------------------------------------------------------------------------------------------------
  const char* deinternString(StringId strId)
  {
    ASSERT(g_stringIdTable.find(strId) != g_stringIdTable.end());

    return g_stringIdTable[strId];
  }
}
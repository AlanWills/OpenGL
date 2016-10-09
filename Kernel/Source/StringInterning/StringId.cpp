#include "StringInterning/StringId.h"
#include "DebugUtils/Debug.h"

namespace Kernel
{
  static std::unordered_map<StringId, std::string> g_stringIdTable;
  static std::unordered_map<std::string, StringId> g_idStringTable;   // Used for quick interning

  //------------------------------------------------------------------------------------------------
  StringId internString(const std::string& str)
  {
    StringId strId = stringToStringId(str.c_str());

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
  StringId internStringFast(const std::string& str)
  {
    ASSERT(g_idStringTable.find(str) != g_idStringTable.end());
    return g_idStringTable[str];
  }

  //------------------------------------------------------------------------------------------------
  const std::string& deinternString(StringId strId)
  {
    ASSERT(g_stringIdTable.find(strId) != g_stringIdTable.end());

    return g_stringIdTable[strId];
  }
}
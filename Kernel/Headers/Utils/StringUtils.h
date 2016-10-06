#pragma once

#include "DllExport.h"

#include <string>

namespace Kernel
{

/// Provides extra utility functions for strings
class DllExport StringUtils
{
  public:
    /// \brief Convert a long string to a normal string and returns the number of characters in the converted string
    static size_t wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer);

    /// \brief Calls to_string on the input and appends it onto the outputStr
    /// Should only be used on primitive numeric types
    /// Cannot control formatting of string so there may be trailing zeroes
    template <typename T>
    static void numericToStringAppend(T input, std::string& outputStr);
};

//------------------------------------------------------------------------------------------------
template <typename T>
void StringUtils::numericToStringAppend(T input, std::string& outputStr)
{
  outputStr.append(std::to_string(input));
}

}
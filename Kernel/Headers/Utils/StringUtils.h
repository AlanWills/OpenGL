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

    /// \brief Converts the inputted int to a string and appends it onto the outputStr
    static void intToStringAppend(int input, std::string& outputStr);
};

}
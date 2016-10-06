#pragma once

#include "DllExport.h"

namespace Kernel
{

/// Provides extra utility functions for strings
class DllExport StringUtils
{
  public:
    /// \brief Convert a long string to a normal string and returns the number of characters in the converted string
    static size_t wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer);
};

}
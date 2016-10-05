#pragma once

#include "DllExport.h"

namespace Kernel
{

/// Provides extra utility functions for strings
class DllExport StringUtils
{
  public:
    static void wcharToChar(const wchar_t* input, char* output, size_t size);
};

}
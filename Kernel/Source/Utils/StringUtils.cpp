#include "Utils/StringUtils.h"
#include <stdlib.h> 

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  void StringUtils::wcharToChar(const wchar_t* input, char* output, size_t size)
  {
    size_t numConverted = 0;
    wcstombs_s(&numConverted, output, size, input, size);
  }
}
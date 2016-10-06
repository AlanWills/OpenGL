#include "Utils/StringUtils.h"
#include <stdlib.h> 

namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  size_t StringUtils::wcharToChar(const wchar_t* input, char* output, size_t sizeOfOutputBuffer)
  {
    size_t numConverted = 0;
    wcstombs_s(&numConverted, output, sizeOfOutputBuffer, input, sizeOfOutputBuffer);

    return numConverted;
  }
}
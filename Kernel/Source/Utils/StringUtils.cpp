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

  //------------------------------------------------------------------------------------------------
  size_t StringUtils::charToWchar(const char* input, wchar_t* output, size_t sizeOfOutputBuffer)
  {
    size_t numConverted = 0;
    return mbstowcs_s(&numConverted, output, sizeOfOutputBuffer, input, sizeOfOutputBuffer);

    return numConverted;
  }

  //------------------------------------------------------------------------------------------------
  std::wstring StringUtils::intToWchar(int number, size_t base)
  {
    wchar_t buffer[1024];
    _itow_s(number, buffer, base);

    return std::wstring(buffer);
  }
}
#include "stdafx.h"
#include "Utils/StringUtils.h"

using namespace Kernel;

namespace TestKernel
{
  TEST_CLASS(TestStringUtils)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringUtils_WcharToChar)
    {
      std::wstring w_string(L"Test String");
      char string[50];

      size_t amountConverted = StringUtils::wcharToChar(w_string.c_str(), string, 50);

      Assert::AreEqual("Test String", string);
      Assert::AreEqual((size_t)12, amountConverted);
    }
  };
}
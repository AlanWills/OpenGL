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

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringUtils_IntToStringAppend)
    {
      {
        std::string actual;
        StringUtils::numericToStringAppend(0, actual);

        Assert::AreEqual("0", actual.c_str());
      }

      {
        std::string actual;
        StringUtils::numericToStringAppend(1010101010, actual);

        Assert::AreEqual("1010101010", actual.c_str());
      }

      {
        std::string actual("Hello");
        StringUtils::numericToStringAppend(-9999999, actual);

        Assert::AreEqual("Hello-9999999", actual.c_str());
      }

      {
        std::string actual("Hello");
        StringUtils::numericToStringAppend(-0.00054f, actual);

        Assert::AreEqual("Hello-0.000540", actual.c_str());
      }
    }
  };
}
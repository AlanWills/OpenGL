#include "stdafx.h"
#include "StringInterning/StringId.h"

using namespace Kernel;

namespace TestKernel
{		
	TEST_CLASS(TestStringId)
	{
	public:
		
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_SameStringsEqualId)
		{
      const char* string = "Test String";

      StringId firstStringId = internString(string);
      StringId secondStringId = internString(string);

      Assert::AreEqual(firstStringId, secondStringId);
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_DifferentStringsNotEqualId)
    {
      const char* firstString = "First String";
      const char* secondString = "Second String";

      StringId firstStringId = internString(firstString);
      StringId secondStringId = internString(secondString);

      Assert::AreNotEqual(firstStringId, secondStringId);
    }
	};
}
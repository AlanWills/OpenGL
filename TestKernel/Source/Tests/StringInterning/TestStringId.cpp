#include "stdafx.h"
#include "StringInterning/StringId.h"

using namespace Kernel;

namespace TestKernel
{		
	TEST_CLASS(TestStringId)
	{
	public:
		
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_InternString_SameStringsEqualId)
		{
      std::string string("Test String");

      StringId firstStringId = internString(string);
      StringId secondStringId = internString(string);

      Assert::AreEqual(firstStringId, secondStringId);
		}

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_InternString_DifferentStringsNotEqualId)
    {
      std::string firstString("First String");
      std::string secondString("Second String");

      StringId firstStringId = internString(firstString);
      StringId secondStringId = internString(secondString);

      Assert::AreNotEqual(firstStringId, secondStringId);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_InternStringFast)
    {
      std::string string("Test String") ;

      StringId firstStringId = internString(string);

      // Lookup the same string to see if internStringFast finds the same StringId
      StringId secondStringId = internStringFast(string);

      Assert::AreEqual(firstStringId, secondStringId);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_StringId_DeinternString)
    {
      std::string firstString("First String");
      std::string secondString("Second String");

      StringId firstStringId = internString(firstString);
      StringId secondStringId = internString(secondString);

      Assert::AreEqual(firstString, deinternString(firstStringId));
      Assert::AreEqual(secondString, deinternString(secondStringId));
    }
	};
}
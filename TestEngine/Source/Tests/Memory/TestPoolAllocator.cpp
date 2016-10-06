#include "stdafx.h"

#include "Memory/PoolAllocator.h"

using namespace Engine;

namespace TestEngine
{
  /*
  In this class we use ints specifically and do not test other types
  Should the need arise, extra types may need to be tested, but functionally I currently believe these tests provide enough coverage
  */
  TEST_CLASS(TestPoolAllocator)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_PoolAllocator_Constructor_NoErrors)
    {
      PoolAllocator<int, 10> intPool;
      PoolAllocator<char, 10> charPool;
      PoolAllocator<void*, 10> pointerPool;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_PoolAllocator_Allocate)
    {
      PoolAllocator<int, 1> intPool;
      int* intObject = intPool.allocate();

      Assert::IsNotNull(intObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_PoolAllocator_CanAllocate)
    {
      PoolAllocator<int, 1> intPool;
      Assert::IsTrue(intPool.canAllocate());

      intPool.allocate();
      Assert::IsFalse(intPool.canAllocate());
    }
  };
}
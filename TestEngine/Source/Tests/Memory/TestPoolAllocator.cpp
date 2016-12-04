#include "stdafx.h"

#include "Memory/PoolAllocator.h"

using namespace OpenGL;

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

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_PoolAllocator_FreeAll)
    {
      PoolAllocator<int, 10> intPool;
      int* intObject = intPool.allocate();

      // Do some more allocation just to move the head
      intPool.allocate();

      // Free everything
      intPool.freeAll();

      // Check the object we allocate is the first one in our pool
      Assert::AreEqual(intObject, intPool.allocate());
    }
  };
}
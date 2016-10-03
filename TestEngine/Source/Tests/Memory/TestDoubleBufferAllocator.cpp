#include "stdafx.h"

#include "Memory/DoubleBufferAllocator.h"

using namespace Engine;

namespace TestEngine
{
  /*
    In this class we use ints specifically and do not test other types
    Should the need arise, extra types may need to be tested, but functionally I currently believe these tests provide enough coverage
  */
  TEST_CLASS(TestDoubleBufferAllocator)
  {
  public:

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Constructor_NoErrors)
    {
      DoubleBufferAllocator<char, 1> charAllocator;
      DoubleBufferAllocator<int, 1024> intAllocator;
      DoubleBufferAllocator<void*, 1024> pointerAllocator;
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CanAllocate)
    {
      DoubleBufferAllocator<void*, 1024> allocator;
      
      std::vector<int> validAllocs = { 1, 10, 1024 };
      std::vector<int> invalidAllocs = { 1025, -1, 0, INT_MAX };

      for (int validSize : validAllocs)
      {
        Assert::IsTrue(allocator.canAllocate(validSize));
      }

      for (int invalidSize : invalidAllocs)
      {
        Assert::IsFalse(allocator.canAllocate(invalidSize));
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      intAllocator.copyAllocate(&data.front(), data.size());
      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_Swapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData(1023);
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      intAllocator.copyAllocate(&offsetData.front(), offsetData.size());
      intAllocator.copyAllocate(&data.front(), data.size());
      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < data.size(); ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_Offsetted_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData = { 0, 0, 0, 0, 0 };
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first five elements (even though we are not filling them out)
      intAllocator.copyAllocate(&offsetData.front(), offsetData.size());
      intAllocator.copyAllocate(&data.front(), data.size());
      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[offsetData.size() + i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* data = intAllocator.pointerAllocate(5);

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_Swapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      intAllocator.pointerAllocate(1023);
      int* data = intAllocator.pointerAllocate(5);

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < 5; ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_Offsetted_NoSwapping)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int offset = 5;

      // Fake allocate the first five elements (even though we are not filling them out)
      intAllocator.pointerAllocate(offset);
      int* data = intAllocator.pointerAllocate(5);

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = intAllocator.getBufferedData();

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[offset + i]);
      }
    }
  };
}
#include "stdafx.h"

#include "Memory/DoubleBufferAllocator.h"

using namespace OpenGL;

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
      
      std::vector<size_t> validAllocs = { 1, 10, 1024 };
      std::vector<size_t> invalidAllocs = { 1025, 0, INT_MAX };

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
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_NoFlushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.copyAllocate(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual(data.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_Flushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData(1023);
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.copyAllocate(offsetData.size(), &offsetData.front()));
      Assert::AreEqual(AllocateResult::kFlushRequired, intAllocator.copyAllocate(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual(data.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(data[i], bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_CopyAllocate_Offsetted_NoFlushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      std::vector<int> offsetData = { 0, 0, 0, 0, 0 };
      std::vector<int> data = { 0, 5, 10, 15, 20 };

      // Fake allocate the first five elements (even though we are not filling them out)
      // Check the allocate result to ensure the validity of our test (if it has flushed then obviously this test is broken!)
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.copyAllocate(offsetData.size(), &offsetData.front()));
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.copyAllocate(data.size(), &data.front()));
      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array and offset data array
      Assert::AreEqual(data.size() + offsetData.size(), bufferUsage);

      for (int i = 0; i < data.size(); ++i)
      {
        Assert::AreEqual(data[i], bufferStart[offsetData.size() + i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_NoFlushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* data = nullptr;
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.pointerAllocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual((size_t)5, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_Flushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int* data = nullptr;

      // Fake allocate the first 1023 elements (even though we are not filling them out)
      // Check the allocate result to ensure the validity of our test (if it has flushed then obviously this test is broken!)
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.pointerAllocate(1023, &data));
      Assert::AreEqual(AllocateResult::kFlushRequired, intAllocator.pointerAllocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array
      Assert::AreEqual((size_t)5, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        // Buffered data should have been completely written to the start of the back buffer
        Assert::AreEqual(i * 5, bufferStart[i]);
      }
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Test_DoubleBufferAllocator_Allocator_PointerAllocate_Offsetted_NoFlushing)
    {
      DoubleBufferAllocator<int, 1024> intAllocator;
      int offset = 5;

      // Fake allocate the first five elements (even though we are not filling them out)
      int* data = nullptr;
      intAllocator.pointerAllocate(offset, &data);
      Assert::AreEqual(AllocateResult::kNoFlushRequired, intAllocator.pointerAllocate(5, &data));

      for (int i = 0; i < 5; ++i)
      {
        data[i] = i * 5;
      }

      intAllocator.swapBuffers();

      const int* bufferStart = nullptr;
      size_t bufferUsage = intAllocator.getBufferedData(&bufferStart);

      // Check we have used the amount of space in the back buffer as our data array and offset
      Assert::AreEqual((size_t)10, bufferUsage);

      for (int i = 0; i < 5; ++i)
      {
        Assert::AreEqual(i * 5, bufferStart[offset + i]);
      }
    }
  };
}

//----------------------------------------------------------------------------------------------------------
// Implementation of ToString for allocate result so that we can use Assert::AreEqual on AllocateResult enum
namespace Microsoft {
  namespace VisualStudio {
    namespace CppUnitTestFramework {

      template<>
      static std::wstring ToString<AllocateResult>(const AllocateResult  & coord) 
      {
        switch (coord)
        {
          case AllocateResult::kFlushRequired:
            return L"FlushRequired";

          case AllocateResult::kNoFlushRequired:
            return L"NoFlushRequired";

          default:
            Assert::Fail();
            return L"";
        }
      }
    }
  }
}
#pragma once

#include "DebugUtils/Debug.h"
#include "AllocatorIterator.h"
#include "Allocator.h"

#include <iterator>


namespace OpenGL
{

/// A memory allocator which creates a large pool of objects in a contiguous array
/// Allocating from this consists of obtaining a pointer to an object in the pool not currently used
template <typename T, size_t PoolSize>
class PoolAllocator : public Allocator<T, PoolSize>
{
  public:
    PoolAllocator();
    virtual ~PoolAllocator();

    /// \brief Returns true if we have free objects in the pool to allocate
    bool canAllocate() const override { return m_head != PoolSize; }

    /// \brief Obtain a handle to a free object from this pool
    /// The object will have already been constructed
    /// This class still retains ownership of the object
    Handle<T> allocate() override;

    /// \brief Deallocates the object at the inputted memory address in this allocator.
    /// The memory will have to be defragmented later, as our head may be past the inputted address.
    void deallocate(T* item) override;

    /// \brief Resets the head to the start of the pool
    void deallocateAll();

    /// \brief Sorts the underlying objects so that all the allocated objects are at the front of the buffer
    /// in a contiguous block.  Handle pointers are updated when we swap memory around to preserve the obejcts they are handles to.
    void defragment() override;

    AllocatorIterator<T> end() override { return AllocatorIterator<T>(&m_pool[m_head]); }

  protected:
    size_t m_head;
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
PoolAllocator<T, PoolSize>::PoolAllocator() :
  m_head(0)
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
PoolAllocator<T, PoolSize>::~PoolAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Handle<T> PoolAllocator<T, PoolSize>::allocate()
{
  ASSERT(canAllocate());

  int freeIndex = 0;
  for (int i = 0; i < PoolSize; ++i)
  {
    if (!m_handles[i])
    {
      freeIndex = i;
      break;
    }
  }

  ASSERT(!m_handles[freeIndex]);
  m_handles[freeIndex] = &(m_pool[m_head++]);

  return Handle<T>(m_handles + freeIndex);
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::deallocate(T* item)
{
  int index = (item - m_pool) / sizeof(T);

  ASSERT(index >= 0 && (index < PoolSize))
  ASSERT(m_handles[index]);

  // If we have deallocated an element that is not on the end of the block of allocated elements, this pool needs defragmenting
  m_needsDefragmenting = m_needsDefragmenting || (index != m_head - 1);
  m_handles[index] = nullptr;
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::deallocateAll()
{
  for (int i = 0; i < PoolSize; ++i)
  {
    deallocate(&m_pool[i]);
  }

  m_head = 0;
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::defragment()
{
  // Iterate on all the items up to head (this is the max we have deallocated)
  // Start at the beginning, move first element we find that is allocated to the front
  // Then continue until we find the next one and move it to the second place
  // Once we have reached head we can stop.

  if (!m_needsDefragmenting)
  {
    // If we do not need to defragment, then don't!
    ASSERT_FAIL();
    return;
  }
  
  int nextDest = 0;

  for (int i = 0; i < PoolSize; ++i)
  {
    if (m_handles[i])
    {
      // We have found an unallocated element and since the handle points to an index which is != nextDest
      // we have empty space in our pool
      int handleIndex = m_handles[i] - m_pool;

      if (handleIndex != nextDest)
      {
        // If we aren't going to move it to the same place we swap the element in the handle index and
        // move it to the nextDest which corresponds to the next index of the contiguous block of objects
        // at the start of our pool
        std::swap(m_pool[handleIndex], m_pool[nextDest]);

        // Fix up the handle corresponding to the alive object to point to the new location
        m_handles[i] = &(m_pool[nextDest]);
      }

      nextDest++;
    }
  }

  // nextDest is also equivalent to the number of objects we have moved so we can reset the head to
  // the end of our now contiguous block of memory
  m_head = nextDest;
  m_needsDefragmenting = false;
}

};
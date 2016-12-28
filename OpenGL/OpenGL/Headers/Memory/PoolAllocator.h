#pragma once

#include "DebugUtils/Debug.h"
#include "PoolAllocatorIterator.h"
#include "Handle.h"

#include <iterator>


namespace OpenGL
{

/// A memory allocator which creates a large pool of objects in a contiguous array
/// Allocating from this consists of obtaining a pointer to an object in the pool not currently used
template <typename T, size_t PoolSize>
class PoolAllocator
{
  public:
    PoolAllocator();
    virtual ~PoolAllocator();

    /// \brief Returns true if we have free objects in the pool to allocate
    bool canAllocate() const { return m_head != PoolSize; }

    /// \brief Obtain a handle to a free object from this pool
    /// The object will have already been constructed
    /// This class still retains ownership of the object
    Handle<T> allocate();

    /// \brief Deallocates the object at the inputted memory address in this allocator.
    /// The memory will have to be defragmented later, as our head may be past the inputted address.
    void deallocate(T* item);

    /// \brief Resets the head to the start of the pool
    void deallocateAll();

    /// \brief Sorts the underlying objects so that all the allocated objects are at the front of the buffer
    /// in a contiguous block.  Handle pointers are updated when we swap memory around to preserve the obejcts they are handles to.
    void defragment();

    virtual PoolAllocatorIterator<T> begin() { return PoolAllocatorIterator<T>(m_pool); }
    virtual PoolAllocatorIterator<T> end() { return PoolAllocatorIterator<T>(&(m_pool[m_head])); }

  protected:
    size_t m_head;
    T m_pool[PoolSize];
    T* m_handles[PoolSize];
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
PoolAllocator<T, PoolSize>::PoolAllocator() :
  m_head(0)
{
  // Construct all the objects - I think this is necessary
  for (size_t i = 0; i < PoolSize; ++i)
  {
    new (&(m_pool[i])) T();
    m_handles[i] = nullptr;
  }
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
  ASSERT(!m_handles[m_head]);

  m_handles[m_head] = &(m_pool[m_head]);

  Handle<T> h(m_handles + m_head);
  m_head++;

  return h;
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::deallocate(T* item)
{
  int index = (item - m_pool) / sizeof(T);

  ASSERT(index >= 0 && (index < PoolSize))
  ASSERT(m_handles[index]);

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

  int nextDest = 0;

  for (int i = 0; i < m_head; ++i)
  {
    if (m_handles[i])
    {
      // We have found an unallocated element and since i != nextDest we have empty space in our pool

      if (i != nextDest)
      {
        // If we aren't going to move it to the same place we swap the element in the current index and
        // move it to the nextDest which corresponds to the next index of the contiguous block of objects
        // at the start of our pool
        std::swap(m_pool[i], m_pool[nextDest]);

        // Having swapped the elements we need to update the handles
        ASSERT(!m_handles[nextDest]);
        m_handles[nextDest] = &(m_pool[i]);

        // Reset this handle to be deallocated
        m_handles[i] = nullptr;
      }

      nextDest++;
    }
  }

  // nextDest is also equivalent to the number of objects we have moved so we can reset the head to
  // the end of our now contiguous block of memory
  m_head = nextDest;
}

};
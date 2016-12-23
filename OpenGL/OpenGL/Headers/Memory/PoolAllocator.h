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

    virtual PoolAllocatorIterator<T> begin() { return PoolAllocatorIterator<T>(m_pool); }
    virtual PoolAllocatorIterator<T> end() { return PoolAllocatorIterator<T>(&(m_pool[m_head])); }

  protected:
    size_t m_head;
    T m_pool[PoolSize];
    bool m_deallocated[PoolSize];
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
    m_deallocated[i] = true;
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
  ASSERT(m_deallocated[m_head]);

  m_deallocated[m_head] = false;
  return Handle<T>(&(m_pool[m_head++]));
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::deallocate(T* item)
{
  int index = (item - m_pool) / sizeof(T);

  ASSERT(index >= 0 && (index < PoolSize))
  ASSERT(!m_deallocated[index]);

  m_deallocated[index] = true;
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

};
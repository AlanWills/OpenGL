#pragma once

#include "DebugUtils/Debug.h"
#include "PoolAllocatorIterator.h"

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

    /// \brief Obtain a pointer to a free object from this pool
    /// The object will have already been constructed
    /// This class still retains ownership of the object
    T* allocate();

    /// \brief Resets the head to the start of the pool
    void freeAll();

    virtual PoolAllocatorIterator<T> begin() { return PoolAllocatorIterator<T>(m_pool); }
    virtual PoolAllocatorIterator<T> end() { return PoolAllocatorIterator<T>(&(m_pool[m_head])); }

  protected:
    size_t m_head;
    T m_pool[PoolSize];
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
  }
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
PoolAllocator<T, PoolSize>::~PoolAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
T* PoolAllocator<T, PoolSize>::allocate()
{
  ASSERT(canAllocate());
  return &(m_pool[m_head++]);
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::freeAll()
{
  m_head = 0;
}

};
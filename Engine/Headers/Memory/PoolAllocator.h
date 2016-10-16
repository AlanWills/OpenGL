#pragma once

#include "DllExport.h"
#include "DebugUtils/Debug.h"

namespace Engine
{

/// A memory allocator which creates a large pool of objects in a contiguous array
/// Allocating from this consists of obtaining a pointer to an object in the pool not currently used
template <typename T, size_t PoolSize>
class PoolAllocator
{
  public:
    PoolAllocator();
    ~PoolAllocator();

    /// \brief Returns true if we have free objects in the pool to allocate
    bool canAllocate() { return m_head != PoolSize; }

    /// \brief Obtain a pointer to a free object from this pool
    /// The object will have already been constructed
    /// This class still retains ownership of the object
    T* allocate();

    /// \brief Resets the head to the start of the pool
    void freeAll();

  private:
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
    new (&m_pool[i]) T();
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
  return &m_pool[m_head++];
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void PoolAllocator<T, PoolSize>::freeAll()
{
  m_head = 0;
}

};
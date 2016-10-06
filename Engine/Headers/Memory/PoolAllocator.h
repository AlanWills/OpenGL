#pragma once

#include "DllExport.h"
#include "Debug.h"

namespace Engine
{

/// A memory allocator which creates a large pool of objects in a contiguous array
/// Allocating from this consists of obtaining a pointer to an object in the pool not currently used
template <typename T, size_t PoolSize>
class DllExport PoolAllocator
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

    /// \brief Marks the object as free to be allocated again
    void free(T* objectToFree);

  private:
    size_t m_head;
    T m_pool[PoolSize];
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
PoolAllocator<T, PoolSize>::PoolAllocator() :
  m_head(0)
{
  // Construct all the objects
  for (size_t i = 0; i < PoolSize; ++i)
  {
    m_pool[i] = T();
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
void PoolAllocator<T, PoolSize>::free(T* objectToFree)
{
  // TODO
  ASSERT_FAIL();
}

};
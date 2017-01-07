#pragma once

#include "Handle.h"
#include "AllocatorIterator.h"


namespace OpenGL
{

template <typename T, size_t PoolSize>
class Allocator
{
  public:
    Allocator();
    virtual ~Allocator();

    virtual bool canAllocate() const = 0;
    virtual Handle<T> allocate() = 0;
    virtual void deallocate(T* item) = 0;
    virtual void defragment() = 0;

    /// \brief Do not want to unnecessarily defragment this allocator
    /// This bool returns the current fragmentation state of the allocator
    bool needsDefragmenting() const { return m_needsDefragmenting; }

    /// \brief Utility function for creating a handle from an object.
    /// We iterate over our handle pointer array and attempt to find a pointer matching the input.
    /// If successful, we return a handle with the address of the matching handle pointer.
    Handle<T> getHandle(T* item) const;

    /// \brief Iterate through the handles array and establish whether the inputted item has been allocated.
    /// Returns true if it has, false otherwise.
    bool isAllocated(T* item) const;

    virtual AllocatorIterator<T> begin() { return AllocatorIterator<T>(m_pool); }
    virtual AllocatorIterator<T> end() { return AllocatorIterator<T>(&m_pool[PoolSize]); }

  protected:
    T m_pool[PoolSize];
    T* m_handles[PoolSize];
    bool m_needsDefragmenting;
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Allocator<T, PoolSize>::Allocator() :
  m_needsDefragmenting(false)
{
  // Construct all the objects
  for (size_t i = 0; i < PoolSize; ++i)
  {
    new (&(m_pool[i])) T();
    m_handles[i] = nullptr;
  }
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Allocator<T, PoolSize>::~Allocator()
{
}


//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Handle<T> Allocator<T, PoolSize>::getHandle(T* item) const
{
  if (!item)
  {
    ASSERT_FAIL();
    return Handle<T>(nullptr);
  }

  for (const T* handle : m_handles)
  {
    if (handle == item)
    {
      return Handle<T>(&handle);
    }
  }

  ASSERT_FAIL();
  return Handle<T>(nullptr);
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
bool Allocator<T, PoolSize>::isAllocated(T* item) const
{
  for (const T* handle : m_handles)
  {
    if (handle == item)
    {
      return true;
    }
  }

  return false;
}

}
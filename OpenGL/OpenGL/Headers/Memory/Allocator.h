#pragma once

#include "Handle.h"


namespace OpenGL
{

template <typename T, size_t PoolSize>
class Allocator
{
  public:
    Allocator();
    virtual ~Allocator();

    virtual bool canAllocate() = 0;
    virtual Handle<T> allocate() = 0;
    virtual void deallocate(T* item) = 0;

  protected:
    T m_pool[PoolSize];
    T* m_handles[PoolSize];
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Allocator<T, PoolSize>::Allocator()
{
  // Construct all the objects
  for (size_t i = 0; i < PoolSize; ++i)
  {
    new (&(m_pool[i])) T();
    m_handles[i] = nullptr;
  }
}

//------------------------------------------------------------------------------------------------
template <typename T, PoolSize>
Allocator<T, PoolSize>::~Allocator()
{
}

}
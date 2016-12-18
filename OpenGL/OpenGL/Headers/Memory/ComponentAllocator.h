#pragma once

// This should call die
// Need an iterator which skips objects not alive and past the head
// Debug memory with an overflow

#include "PoolAllocator.h"
#include "ComponentAllocatorIterator.h"


namespace OpenGL
{

/// A memory allocator specifically for managing components
/// As well as using a PoolAllocator, component state is managed when allocating and deallocating
template <typename T, size_t PoolSize>
class ComponentAllocator : public PoolAllocator<T, PoolSize>
{
  public:
    ComponentAllocator();
    virtual ~ComponentAllocator();

    /// \brief Allocates and returns a pointer to a component.
    /// The component will have had initialize already called on it.
    T* allocateAndInitialize();

    PoolAllocatorIterator<T> begin() { return ComponentAllocatorIterator<T>(m_pool, &(m_pool[m_head])); }
    PoolAllocatorIterator<T> end() { return ComponentAllocatorIterator<T>(&(m_pool[m_head]), &(m_pool[m_head])); }
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
ComponentAllocator<T, PoolSize>::ComponentAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
ComponentAllocator<T, PoolSize>::~ComponentAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
T* ComponentAllocator<T, PoolSize>::allocateAndInitialize()
{
  T* component = allocate();
  component->initialize();

  return component;
}

}
#pragma once

// This should call die
// Need an iterator which skips objects not alive and past the head
// Debug memory with an overflow

#include "PoolAllocator.h"
#include "ComponentAllocatorIterator.h"


namespace OpenGL
{

/// A memory allocator specifically for managing components
/// Uses the inputted allocator to manage the components
template <typename AllocatorType, typename T, size_t PoolSize>
class ComponentAllocator
{
  public:
    ComponentAllocator();
    virtual ~ComponentAllocator();

    /// \brief Returns true if the underlying allocator's canAllocate function returns true.
    /// Otherwise, returns false.
    bool canAllocate() const { return m_allocator.canAllocate(); }

    /// \brief Allocates and returns a handle using the templated allocator.
    Handle<T> allocate() { return m_allocator.allocate(); }

    /// \brief Allocates and returns a handle using the templated allocator
    /// The component will have had initialize already called on it.
    Handle<T> allocateAndInitialize();

    /// \brief Free the memory reserved in the templated allocator for reuse.
    void deallocate(T* item) { m_allocator.deallocate(item); }

    AllocatorIterator<T> begin() 
    {
      ComponentAllocatorIterator<T>& it = ComponentAllocatorIterator<T>(*m_allocator.begin() - 1, *m_allocator.end());
      return ++it;
    }

    AllocatorIterator<T> end() { return ComponentAllocatorIterator<T>(*m_allocator.end(), *m_allocator.end()); }

    void awake();
    void handleInput(GLfloat elapsedGameTime);
    void update(GLfloat secondsPerUpdate);
    void render(GLfloat lag);
    void die();

  private:
    AllocatorType m_allocator;
};

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
ComponentAllocator<AllocatorType, T, PoolSize>::ComponentAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
ComponentAllocator<AllocatorType, T, PoolSize>::~ComponentAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
Handle<T> ComponentAllocator<AllocatorType, T, PoolSize>::allocateAndInitialize()
{
  ASSERT(m_allocator.canAllocate());
  Handle<T> component = m_allocator.allocate();
  component->initialize(component);

  return component;
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
void ComponentAllocator<AllocatorType, T, PoolSize>::awake()
{
  for (T* component : *this)
  {
    component->awake();
  }
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
void ComponentAllocator<AllocatorType, T, PoolSize>::handleInput(GLfloat elapsedGameTime)
{
  for (T* component : *this)
  {
    component->handleInput(elapsedGameTime);
  }
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
void ComponentAllocator<AllocatorType, T, PoolSize>::update(GLfloat secondsPerUpdate)
{
  for (T* component : m_allocator)
  {
    // Go through all elements and check to see if any are dead and deallocate them
    if (!component->isAlive() && m_allocator.isAllocated(component))
    {
      deallocate(component);
    }
  }

  for (T* component : *this)
  {
    component->update(secondsPerUpdate);
  }

  if (m_allocator.needsDefragmenting())
  {
    m_allocator.defragment();
  }
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
void ComponentAllocator<AllocatorType, T, PoolSize>::render(GLfloat lag)
{
  for (T* component : *this)
  {
    component->render(lag);
  }
}

//------------------------------------------------------------------------------------------------
template <typename AllocatorType, typename T, size_t PoolSize>
void ComponentAllocator<AllocatorType, T, PoolSize>::die()
{
  for (T* component : *this)
  {
    component->die();
  }
}

}
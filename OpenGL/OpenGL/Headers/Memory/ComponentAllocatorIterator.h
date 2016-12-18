#pragma once

#include "PoolAllocatorIterator.h"


namespace OpenGL
{

template <typename T>
class ComponentAllocatorIterator : public PoolAllocatorIterator<T>
{
  public:
    ComponentAllocatorIterator(T* ptr, T* end);
    virtual ~ComponentAllocatorIterator();

    PoolAllocatorIterator& operator++() override;
    PoolAllocatorIterator operator++(int) override;

    T* operator*() const { return m_ptr; }

  protected:
    T* m_end;
};

//------------------------------------------------------------------------------------------------
template <typename T>
ComponentAllocatorIterator<T>::ComponentAllocatorIterator(T* ptr, T* end) :
  PoolAllocatorIterator<T>(ptr),
  m_end(end)
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
ComponentAllocatorIterator<T>::~ComponentAllocatorIterator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
PoolAllocatorIterator<T>& ComponentAllocatorIterator<T>::operator++()
{
  ++m_ptr;
  while (m_ptr != m_end && !m_ptr->isAlive())
  {
    ++m_ptr;
  }

  return *this;
}

//------------------------------------------------------------------------------------------------
template <typename T>
PoolAllocatorIterator<T> ComponentAllocatorIterator<T>::operator++(int)
{
  ++m_ptr;
  while (m_ptr != m_end && !m_ptr->isAlive())
  {
    ++m_ptr;
  }

  return ComponentAllocatorIterator<T>(m_ptr, m_end);
}

}
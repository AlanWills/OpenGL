#pragma once

#include "AllocatorIterator.h"


namespace OpenGL
{

template <typename T>
class ComponentAllocatorIterator : public AllocatorIterator<T>
{
  public:
    ComponentAllocatorIterator(T* ptr, T* end);
    virtual ~ComponentAllocatorIterator();

    AllocatorIterator& operator++() override;
    AllocatorIterator operator++(int) override;

    T* operator*() const { return m_ptr; }

  protected:
    T* m_end;
};

//------------------------------------------------------------------------------------------------
template <typename T>
ComponentAllocatorIterator<T>::ComponentAllocatorIterator(T* ptr, T* end) :
  AllocatorIterator<T>(ptr),
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
AllocatorIterator<T>& ComponentAllocatorIterator<T>::operator++()
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
AllocatorIterator<T> ComponentAllocatorIterator<T>::operator++(int)
{
  ++m_ptr;
  while (m_ptr != m_end && !m_ptr->isAlive())
  {
    ++m_ptr;
  }

  return ComponentAllocatorIterator<T>(m_ptr, m_end);
}

}
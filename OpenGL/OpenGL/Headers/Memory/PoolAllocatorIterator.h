#pragma once

#include <iterator>


namespace OpenGL
{

template <typename T>
class PoolAllocatorIterator : std::iterator<std::forward_iterator_tag, T>
{
  public:
    PoolAllocatorIterator(T* ptr);
    
    PoolAllocatorIterator& operator++();
    PoolAllocatorIterator operator++(int);

    bool operator==(PoolAllocatorIterator<T> other) const;
    bool operator!=(PoolAllocatorIterator<T> other) const;

    T* operator*() const { return m_ptr; }

  private:
    T* m_ptr;
};

//------------------------------------------------------------------------------------------------
template <typename T>
PoolAllocatorIterator<T>::PoolAllocatorIterator(T* ptr) :
  m_ptr(ptr)
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
PoolAllocatorIterator<T>& PoolAllocatorIterator<T>::operator++()
{
  ++m_ptr;
  return *this;
}

//------------------------------------------------------------------------------------------------
template <typename T>
PoolAllocatorIterator<T> PoolAllocatorIterator<T>::operator++(int)
{
  PoolAllocatorIterator<T> iterator(++m_ptr);
  return iterator;
}

//------------------------------------------------------------------------------------------------
template <typename T>
bool PoolAllocatorIterator<T>::operator==(PoolAllocatorIterator<T> other) const
{
  return m_ptr == *other;
}

//------------------------------------------------------------------------------------------------
template <typename T>
bool PoolAllocatorIterator<T>::operator!=(PoolAllocatorIterator<T> other) const
{
  return !(m_ptr == *other);
}

}
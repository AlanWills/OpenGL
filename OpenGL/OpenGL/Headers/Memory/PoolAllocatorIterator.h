#pragma once

#include <iterator>


namespace OpenGL
{

template <typename T>
class PoolAllocatorIterator : std::iterator<std::forward_iterator_tag, T>
{
  public:
    PoolAllocatorIterator(T* ptr);
    virtual ~PoolAllocatorIterator();
    
    virtual PoolAllocatorIterator& operator++();
    virtual PoolAllocatorIterator operator++(int);

    bool operator==(PoolAllocatorIterator<T> other) const;
    bool operator!=(PoolAllocatorIterator<T> other) const;

    T* operator*() const { return m_ptr; }

  protected:
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
PoolAllocatorIterator<T>::~PoolAllocatorIterator()
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
  return PoolAllocatorIterator<T>(++m_ptr);
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
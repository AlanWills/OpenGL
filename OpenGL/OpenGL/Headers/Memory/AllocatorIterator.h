#pragma once

#include <iterator>


namespace OpenGL
{

template <typename T>
class AllocatorIterator : std::iterator<std::forward_iterator_tag, T>
{
  public:
    AllocatorIterator(T* ptr);
    virtual ~AllocatorIterator();
    
    virtual AllocatorIterator& operator++();
    virtual AllocatorIterator operator++(int);

    bool operator==(AllocatorIterator<T> other) const;
    bool operator!=(AllocatorIterator<T> other) const;

    T* operator*() const { return m_ptr; }

  protected:
    T* m_ptr;
};

//------------------------------------------------------------------------------------------------
template <typename T>
AllocatorIterator<T>::AllocatorIterator(T* ptr) :
  m_ptr(ptr)
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
AllocatorIterator<T>::~AllocatorIterator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
AllocatorIterator<T>& AllocatorIterator<T>::operator++()
{
  ++m_ptr;
  return *this;
}

//------------------------------------------------------------------------------------------------
template <typename T>
AllocatorIterator<T> AllocatorIterator<T>::operator++(int)
{
  return AllocatorIterator<T>(++m_ptr);
}

//------------------------------------------------------------------------------------------------
template <typename T>
bool AllocatorIterator<T>::operator==(AllocatorIterator<T> other) const
{
  return m_ptr == *other;
}

//------------------------------------------------------------------------------------------------
template <typename T>
bool AllocatorIterator<T>::operator!=(AllocatorIterator<T> other) const
{
  return !(m_ptr == *other);
}

}
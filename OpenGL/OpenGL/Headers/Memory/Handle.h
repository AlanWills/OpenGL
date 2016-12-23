#pragma once


namespace OpenGL
{

// A templated class that is merely a wrapper around a T pointer
// We use it to manage allocated memory for custom allocators and to update pointers when memory is defragmented
template <typename T>
class Handle
{
  public:
    Handle(T* ptr);
    ~Handle();

  private:
    T* m_ptr;
};

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T>::Handle(T* ptr) :
  m_ptr(ptr)
{
}

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T>::~Handle()
{
}

}
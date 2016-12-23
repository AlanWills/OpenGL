#pragma once


namespace OpenGL
{

// A templated struct that is merely a wrapper around a T pointer
// We use it to manage allocated memory for custom allocators and to update pointers when memory is defragmented
template <typename T>
struct Handle
{
  public:
    Handle();
    Handle(T* ptr);
    ~Handle();

    T* operator->() 
    {
      ASSERT(m_ptr);
      return m_ptr; 
    }

    T& operator*()
    {
      ASSERT(m_ptr);
      return *m_ptr;
    }

    const T& operator*() const
    {
      ASSERT(m_ptr);
      return *m_ptr;
    }

    T* get() { return m_ptr; }

    /// \brief Checks to see if the underlying pointer this handle represents is dynamically castable to the inputted type
    template <typename K>
    inline bool is() { return dynamic_cast<K*>(m_ptr) != nullptr; }

    /// \brief Returns a new handle with this handle's pointer dynamically casted to the inputted type.
    template <typename K>
    inline Handle<K> as() 
    {
      ASSERT(is<K>());
      return Handle<K>(dynamic_cast<K*>(m_ptr));
    }

  private:
    T* m_ptr;
};

//------------------------------------------------------------------------------------------------
template <typename T>
Handle<T>::Handle() :
  Handle<T>(nullptr)
{
}

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
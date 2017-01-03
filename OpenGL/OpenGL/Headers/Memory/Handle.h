#pragma once


namespace OpenGL
{

// A templated struct that is merely a wrapper around a T pointer
// We use it to manage allocated memory for custom allocators and to update pointers when memory is defragmented
template <typename T>
struct Handle
{
  public:
    Handle() : m_ptr(nullptr) { }
    Handle(T** ptr) : m_ptr(ptr) { }

    template <typename K>
    Handle(const Handle<K>& handle,
      typename std::enable_if<std::is_convertible<K*, T*>::value, void>::type * = 0)
      : Handle(handle.as<T>()) { }

    ~Handle() { }

    T* operator->() const
    {
      ASSERT(m_ptr);
      return *m_ptr; 
    }

    T& operator*()
    {
      ASSERT(m_ptr);
      return **m_ptr;
    }

    const T& operator*() const
    {
      ASSERT(m_ptr);
      return **m_ptr;
    }

    bool operator==(const Handle<T>& handle) const { return m_ptr == handle.m_ptr; }

    T* get() const { return m_ptr ? *m_ptr : nullptr; }

    /// \brief Checks to see if the underlying pointer this handle represents is dynamically castable to the inputted type
    template <typename K>
    inline bool is() const { return dynamic_cast<K*>(*m_ptr) != nullptr; }

    /// \brief Returns a new handle with this handle's pointer dynamically casted to the inputted type.
    template <typename K>
    inline Handle<K> as() const
    {
      ASSERT(is<K>());
      return Handle<K>(reinterpret_cast<K**>(m_ptr));
    }

  private:
    T** m_ptr;
};

}


namespace std
{
  template <typename T>
  struct hash<OpenGL::Handle<T>>
  {
    std::size_t operator()(const OpenGL::Handle<T>& handle) const
    {
      using std::hash;

      return std::hash<T*>()(handle.get());
    }
  };
}
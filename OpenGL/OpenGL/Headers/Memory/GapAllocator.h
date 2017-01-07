#pragma once

#include "Allocator.h"
#include "Debugging/DebugManager.h"


namespace OpenGL
{

template <typename T, size_t PoolSize>
class GapAllocator : public Allocator<T, PoolSize>
{
public:
  GapAllocator();
  virtual ~GapAllocator();

  /// \brief Returns true if we have free elements within our pool to allocate.
  /// Otherwise returns false.
  bool canAllocate() const override;

  /// \brief Obtain a handle to a free object from this allocator.
  /// The object will have already been constructed, so this class still retains ownership.
  Handle<T> allocate() override;

  /// \brief Deallocates the slot which holds the inputted item.
  /// No defragmentation takes place because the PoolSize is small.
  void deallocate(T* item) override;
};

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
GapAllocator<T, PoolSize>::GapAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
GapAllocator<T, PoolSize>::~GapAllocator()
{
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
bool GapAllocator<T, PoolSize>::canAllocate() const
{
  for (size_t i = 0; i < PoolSize; ++i)
  {
    if (!m_handles[i])
    {
      return true;
    }
  }

  return false;
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
Handle<T> GapAllocator<T, PoolSize>::allocate()
{
  // To establish which elements are unallocated we check the m_handles array.
  // Any element which is nullptr we can allocate
  for (size_t i = 0; i < PoolSize; ++i)
  {
    if (!m_handles[i])
    {
      m_handles[i] = &(m_pool[i]);
      return Handle<T>(&m_handles[i]);
    }
  }

  // We should never get here
  ASSERT_FAIL();
  return Handle<T>();
}

//------------------------------------------------------------------------------------------------
template <typename T, size_t PoolSize>
void GapAllocator<T, PoolSize>::deallocate(T* item)
{
  // Iterate over the pool and find the element corresponding to the inputted pointer
  // We then clear the handle to that item to be nullptr to indicate it is available to be allocated again
  for (size_t i = 0; i < PoolSize; ++i)
  {
    if (m_pool[i] == item)
    {
      ASSERT(+m_handles[i]);
      m_handles[i] = nullptr;
      return;
    }
  }
}

}
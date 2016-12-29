#include "DebugUtils/Debug.h"

#include <string>


namespace Kernel
{
  // Initialise static variable with normal assert
  std::unique_ptr<DebugAssert> Debug::m_assert = std::unique_ptr<DebugAssert>(new DebugAssert());

  //------------------------------------------------------------------------------------------------
  const DebugAssert& Debug::getAssert()
  {
    if (!m_assert.get())
    {
      // Assert cannot be nullptr otherwise bad things happen so create a static NullAssert in case we have registered a nullptr
      // This is a serious final resort
      static NullAssert assert;

      return assert;
    }

    return *m_assert.get();
  }

  //------------------------------------------------------------------------------------------------
  void Debug::setAssert(DebugAssert* assert)
  {
    if (!assert)
    {
      // Again if we are trying to register nullptr, register a null assert instead
      assert = new NullAssert();
    }

    m_assert.reset(assert);
  }
}
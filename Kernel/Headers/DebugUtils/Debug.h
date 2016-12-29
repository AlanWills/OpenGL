#pragma once

#include "DllExport.h"
#include "DebugAssert.h"
#include "NullAssert.h"

#include <iostream>
#include <assert.h>
#include <memory>


#ifdef _DEBUG
#define ASSERT(condition) Kernel::Debug::getAssert().check(condition);
#else
#define ASSERT(condition)
#endif

#define ASSERT_MSG(condition, message) ASSERT(condition && message)

#define ASSERT_FAIL() ASSERT(false)

#define ASSERT_FAIL_MSG(message) ASSERT(false, message)

/// A service locator for custom debug functionality
/// In debug we can disable asserts by registering a NullAssert class, or provide extra info by registering a custom assert class
/// This is different from the assert macros being compiled out in a release
/// Normally use a macro if you wish to have typical Debug in Release out asserts, but asserts can be left in a release build by calling:
///
///       Kernel::Debug::getAssert().check(condition);
///
/// explicitly
namespace Kernel
{

class DllExport Debug
{
  public:
    static const DebugAssert& getAssert();

    /// \brief Set the assert functionality that will run with runtime asserts
    /// This class takes ownership of this now
    static void setAssert(DebugAssert* assert);

  private:
    Debug() = default;
    Debug(const Debug& debug) = default;

    static std::unique_ptr<DebugAssert> m_assert;
};

}
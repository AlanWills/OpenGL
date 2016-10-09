#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <iostream>
#include <assert.h>


DllExport void checkGLError_(const char *file, int line);
#define glCheckError()  checkGLError_(__FILE__, __LINE__)

#ifdef _DEBUG
#define ASSERT(condition) Kernel::Debug::getInstance().debugAssert(condition);
#else
#define ASSERT(condition)
#endif

#define ASSERT_MSG(condition, message) ASSERT(condition && message)

#define ASSERT_FAIL() ASSERT(false)

#define ASSERT_FAIL_MSG(message) ASSERT(false, message)

// A class that provides our own debug functionality
// It is singleton rather than static because I ran into issues in the unit tests with static variables
namespace Kernel
{

class DllExport Debug
{
  public:
    static Debug& getInstance();

    // Have separate assert class
    // Then use service locator pattern to get the assert
    // Have NullAssert which does nothing and DebugAssert which does high info asserting (and maybe runtime assert which is lightweight)
    // Then create a class in TestUtils for turning off Asserts, by attaching a NullAssert in cstr & then attaching DebugAssert in dstr

    void disableAsserts() { m_assertsDisabled = true; }
    void enableAsserts() { m_assertsDisabled = false; }

    void debugAssert(bool condition);

  private:
    Debug() : m_assertsDisabled(false) {}
    Debug(const Debug& debug) = delete;

    // We have this bool so that we can turn off asserts for section of code (like unit tests)
    bool m_assertsDisabled;
};

}
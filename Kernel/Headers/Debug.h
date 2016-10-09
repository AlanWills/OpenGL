#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <iostream>
#include <assert.h>


DllExport void checkGLError_(const char *file, int line);
#define glCheckError()  checkGLError_(__FILE__, __LINE__)

#ifdef _DEBUG
#define ASSERT(condition) Debug::getInstance().debugAssert(condition);
#else
#define ASSERT(condition)
#endif

#define ASSERT_MSG(condition, message) ASSERT(condition && message)

#define ASSERT_FAIL() ASSERT(false)

#define ASSERT_FAIL_MSG(message) ASSERT(false, message)

class DllExport Debug
{
  public:
    static Debug& getInstance();

    void disableAsserts() { m_assertsDisabled = true; }
    void enableAsserts() { m_assertsDisabled = false; }

    void debugAssert(bool condition) { if (!m_assertsDisabled) { assert(condition); } }

  private:
    Debug() : m_assertsDisabled(false) {}
    Debug(const Debug& debug) = delete;

    bool m_assertsDisabled;
};
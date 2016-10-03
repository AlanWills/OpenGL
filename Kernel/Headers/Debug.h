#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <iostream>
#include <assert.h>

DllExport void checkGLError_(const char *file, int line);
#define glCheckError()  checkGLError_(__FILE__, __LINE__)

#if !defined(NDEBUG) && !defined(TESTING)
#define ASSERT_MSG(condition, message) \
  do { \
    if ((!condition)) { \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#define ASSERT_MSG(condition, message) do { } while (false)
#endif

#define ASSERT(condition) \
  ASSERT_MSG(condition, "")
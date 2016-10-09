#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <iostream>
#include <assert.h>


DllExport void checkGLError_(const char *file, int line);
#define glCheckError()  checkGLError_(__FILE__, __LINE__)

#ifdef _DEBUG
#define ASSERT(condition) assert(condition);
#else
#define ASSERT(condition)
#endif

#define ASSERT_MSG(condition, message) ASSERT(condition && message)

#define ASSERT_FAIL() ASSERT(false)

#define ASSERT_FAIL_MSG(message) ASSERT(false, message)
#pragma once

#include "GLHeaders.h"
#include "DllExport.h"

#include <iostream>
#include <assert.h>

DllExport void checkGLError_(const char *file, int line);
#define glCheckError()  checkGLError_(__FILE__, __LINE__)
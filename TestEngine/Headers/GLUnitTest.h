#pragma once

#include "GLHeaders.h"
#include "CppUnitTest.h"

namespace TestEngine
{
  
class GLUnitTest
{
  public:
    GLUnitTest()
    {
      GLFW_INIT();
    }

    virtual ~GLUnitTest()
    {
      GLFW_TERMINATE();
    }
};

};
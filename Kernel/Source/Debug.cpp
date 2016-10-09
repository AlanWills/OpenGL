#include "Debug.h"

#include <string>

#define GL_FATAL_ERROR_NUMBER 3

void checkGLError_(const char *file, int line)
{
  int count = 0;
  GLenum errorCode;

  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string error;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
    case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
    case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
    case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
    case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
    case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
    case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    
    if (++count > GL_FATAL_ERROR_NUMBER)
    {
      // Assert if we have too many errors, otherwise just print them out
      ASSERT(false);
    }
  }
}


namespace Kernel
{
  //------------------------------------------------------------------------------------------------
  Debug& Debug::getInstance()
  {
    static Debug instance;

    return instance;
  }

  //------------------------------------------------------------------------------------------------
  void Debug::debugAssert(bool condition)
  {
    if (!m_assertsDisabled)
    { 
      assert(condition); 
    }
  }
}
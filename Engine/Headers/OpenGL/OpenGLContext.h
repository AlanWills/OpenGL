#pragma once

#include "DllExport.h"
#include "GLHeaders.h"

namespace Engine
{

// A class which is responsible for initialising GLEW, GLFW and OpenGL
class DllExport OpenGLContext
{
  public:
    OpenGLContext();
    ~OpenGLContext();
};

}
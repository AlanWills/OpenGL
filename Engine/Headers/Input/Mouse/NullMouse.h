#pragma once

#include "DllExport.h"
#include "Mouse.h"

namespace Engine
{

class DllExport NullMouse : public Mouse
{
  public:
    NullMouse() { }
    ~NullMouse() { }

    GLboolean isButtonDown(MouseButton mouseButton) const override { return GL_FALSE; }
    GLboolean isButtonPressed(MouseButton mouseButton) const override { return GL_FALSE; }
};

};
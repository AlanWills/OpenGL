#pragma once

#include "Mouse.h"

namespace Engine
{

class DllExport NullMouse : public Mouse
{
  public:
    NullMouse();
    ~NullMouse();

    GLboolean isButtonDown(MouseButton mouseButton) const override;
    GLboolean isButtonPressed(MouseButton mouseButton) const override;
};

};
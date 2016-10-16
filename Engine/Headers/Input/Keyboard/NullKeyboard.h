#pragma once

#include "Keyboard.h"

namespace Engine
{
  class DllExport NullKeyboard : public Keyboard
  {
  public:
    NullKeyboard();
      ~NullKeyboard();

    GLboolean isKeyDown(int key) const override;
    GLboolean isKeyPressed(int key) const override;
  };
}
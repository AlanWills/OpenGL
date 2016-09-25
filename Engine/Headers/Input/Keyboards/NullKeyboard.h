#pragma once

#include "Keyboard.h"

namespace Engine
{
  class NullKeyboard : public Keyboard
  {
    NullKeyboard();
    ~NullKeyboard();

    GLboolean isKeyDown(int key) const override;
    GLboolean isKeyPressed(int key) const override;
  };
}
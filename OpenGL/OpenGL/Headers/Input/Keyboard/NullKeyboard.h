#pragma once

#include "Keyboard.h"

namespace OpenGL
{
  class NullKeyboard : public Keyboard
  {
  public:
    NullKeyboard();
      ~NullKeyboard();

    GLboolean isKeyDown(int key) const override;
    GLboolean isKeyPressed(int key) const override;
  };
}
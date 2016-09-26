#include "stdafx.h"

#include "Input/Keyboard/NullKeyboard.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  NullKeyboard::NullKeyboard()
  {
  }

  //------------------------------------------------------------------------------------------------
  NullKeyboard::~NullKeyboard()
  {
  }

  //------------------------------------------------------------------------------------------------
  GLboolean NullKeyboard::isKeyDown(int key) const
  {
    return GL_FALSE;
  }

  //------------------------------------------------------------------------------------------------
  GLboolean NullKeyboard::isKeyPressed(int key) const
  {
    return GL_FALSE;
  }
}
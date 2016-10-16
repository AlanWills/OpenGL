#include "stdafx.h"

#include "Input/Mouse/NullMouse.h"

namespace Engine
{
  //------------------------------------------------------------------------------------------------
  NullMouse::NullMouse()
  {
  }

  //------------------------------------------------------------------------------------------------
  NullMouse::~NullMouse()
  {
  }

  //------------------------------------------------------------------------------------------------
  GLboolean NullMouse::isButtonDown(MouseButton mouseButton) const 
  { 
    return GL_FALSE; 
  }

  //------------------------------------------------------------------------------------------------
  GLboolean NullMouse::isButtonPressed(MouseButton mouseButton) const 
  { 
    return GL_FALSE; 
  }
}
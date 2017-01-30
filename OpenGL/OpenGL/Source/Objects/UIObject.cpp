#include "stdafx.h"

#include "Objects/UIObject.h"
#include "Viewport/Camera.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  UIObject::UIObject()
  {
  }

  //------------------------------------------------------------------------------------------------
  UIObject::~UIObject()
  {
  }

  //------------------------------------------------------------------------------------------------
  void UIObject::initialize(const Handle<Component>& allocHandle)
  {
    Inherited::initialize(allocHandle);

    attachToCamera(allocHandle.as<GameObject>());
  }
}
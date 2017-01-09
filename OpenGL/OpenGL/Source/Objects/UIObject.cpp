#include "stdafx.h"

#include "Objects/UIObject.h"
#include "Game/GameManager.h"


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
  void UIObject::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    getTransform()->setParent(GameManager::getScreenManager()->getCurrentScreen()->getUIManager().getSceneRoot());
  }
}
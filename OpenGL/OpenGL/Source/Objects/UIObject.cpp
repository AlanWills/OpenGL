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

    // Transform this object's transform into screen coordinates
    m_transform.setLocalMatrix(glm::scale(m_transform.getLocalMatrix(), glm::vec3(GameManager::getScreenManager()->getViewportDimensions(), 1)));
  }
}
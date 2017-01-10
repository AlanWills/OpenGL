#include "stdafx.h"

#include "UI/StackPanel.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  StackPanel::StackPanel()
  {
  }

  //------------------------------------------------------------------------------------------------
  StackPanel::~StackPanel()
  {
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::addChild(Handle<UIObject> uiObject)
  {
    m_children.push_back(uiObject);
  }

  //------------------------------------------------------------------------------------------------
  void StackPanel::calculateLayout()
  {
    // Iterate over all items and arrange them accordingly
  }
}
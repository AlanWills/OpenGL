#include "stdafx.h"

#include "Input/MouseInteractionHandler.h"


namespace OpenGL
{
  REGISTER_COMPONENT(MouseInteractionHandler);

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::MouseInteractionHandler() :
    m_onLeftClick(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::~MouseInteractionHandler()
  {
  }
}
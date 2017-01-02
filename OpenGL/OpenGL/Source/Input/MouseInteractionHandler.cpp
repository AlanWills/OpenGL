#include "stdafx.h"

#include "Input/MouseInteractionHandler.h"
#include "UI/Button.h"


namespace OpenGL
{
  REGISTER_COMPONENT(MouseInteractionHandler);

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::MouseInteractionHandler()
  {
  }

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::~MouseInteractionHandler()
  {
  }

  void MouseInteractionHandler::test()
  {
    /*Button* button = getParent().as<Button>().get();
    (button->*m_onLeftClick)();*/
  }
}
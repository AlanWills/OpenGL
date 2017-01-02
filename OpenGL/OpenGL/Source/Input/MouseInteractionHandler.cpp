#include "stdafx.h"

#include "Input/MouseInteractionHandler.h"
#include "Game/GameManager.h"
#include "Objects/GameObject.h"


namespace OpenGL
{
  REGISTER_COMPONENT(MouseInteractionHandler);

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::MouseInteractionHandler() :
    m_isMouseOver(false),
    m_collider(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  MouseInteractionHandler::~MouseInteractionHandler()
  {
  }

  //------------------------------------------------------------------------------------------------
  void MouseInteractionHandler::awake()
  {
    Inherited::awake();

    m_collider = getParent()->findComponent<Collider>();
    ASSERT(m_collider.get());
  }

  //------------------------------------------------------------------------------------------------
  void MouseInteractionHandler::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    Mouse* mouse = GameManager::getInputManager()->getMouse();

    bool mouseOverThisFrame = m_collider->intersectsPoint(mouse->getMousePosition());

    if (mouseOverThisFrame && !m_isMouseOver)
    {
      m_onEnter.invoke(getParent());
    }
    else if (!mouseOverThisFrame && m_isMouseOver)
    {
      m_onLeave.invoke(getParent());
    }

    m_isMouseOver = mouseOverThisFrame;
  }
}
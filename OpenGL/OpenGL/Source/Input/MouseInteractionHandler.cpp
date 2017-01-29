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

    bool mouseOverThisFrame = m_collider->intersects(mouse->getMousePosition());

    if (mouseOverThisFrame)
    {
      if (!m_isMouseOver)
      {
        // The mouse is over the collider this frame, but wasn't last frame so it has just entered the collider
        m_onEnter.invoke(getParent());
      }

      if (mouse->isButtonPressed(Mouse::kLeft))
      {
        // The mouse is over the collider this frame and the left mouse button has been pressed - our object has been left clicked
        m_onLeftClick.invoke(getParent());
      }
      else if (mouse->isButtonPressed(Mouse::kMiddle))
      {
        // The mouse is over the collider this frame and the middle mouse button has been pressed - our object has been middle clicked
        m_onMiddleClick.invoke(getParent());
      }
      else if (mouse->isButtonPressed(Mouse::kRight))
      {
        // The mouse is over the collider this frame and the right mouse button has been pressed - our object has been right clicked
        m_onRightClick.invoke(getParent());
      }
    }
    else
    {
      if (m_isMouseOver)
      {
        // The mouse is not over the collider this frame, but was last frame so it has just left the collider
        m_onLeave.invoke(getParent());
      }
    }

    m_isMouseOver = mouseOverThisFrame;
  }
}
#include "stdafx.h"

#include "UI/Button.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Button::Button()
  {
  }

  //------------------------------------------------------------------------------------------------
  Button::~Button()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Button::initialize(Handle<Component> allocHandle)
  {
    Inherited::initialize(allocHandle);

    ADD_AND_INITIALIZE_CLASS_COMPONENT(RectangleCollider, m_collider);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(TextRenderer, m_textRenderer);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction);

    m_spriteRenderer.setTexture("ButtonDefault");

    m_collider.setDimensions(m_spriteRenderer.getDimensions());

    m_transform.setLocalMatrix(glm::scale(m_transform.getLocalMatrix(), glm::vec3(GameManager::getScreenManager()->getViewportDimensions(), 1)));
    m_transform.translate(glm::vec3(200, 200, 0));

    m_mouseInteraction.addOnEnterEvent(std::bind(&Button::onEnter, this, std::placeholders::_1));
    m_mouseInteraction.addOnLeaveEvent(std::bind(&Button::onLeave, this, std::placeholders::_1));
  }

  //------------------------------------------------------------------------------------------------
  void Button::onEnter(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture("ButtonHighlighted");
  }

  //------------------------------------------------------------------------------------------------
  void Button::onLeave(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture("ButtonDefault");
  }
}
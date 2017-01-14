#include "stdafx.h"

#include "UI/Button.h"
#include "Game/GameManager.h"


namespace OpenGL
{
  const float Button::s_maxTime = 0.1f;

  //------------------------------------------------------------------------------------------------
  Button::Button() :
    m_clickTimer(0),
    m_state(kIdle)
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
    ADD_AND_INITIALIZE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction);
    ADD_AND_INITIALIZE_CLASS_COMPONENT(Label, m_label);

    // Anchor the label to this button and move it in front of it slightly
    m_label.getTransform()->setParent(getTransform());
    m_label.getTransform()->translate(glm::vec3(0, 0, 0.1f));

    m_spriteRenderer.setTexture("ButtonDefault.png");

    m_collider.setDimensions(m_spriteRenderer.getDimensions());

    m_mouseInteraction.addOnEnterEvent(std::bind(&Button::onEnter, this, std::placeholders::_1));
    m_mouseInteraction.addOnLeaveEvent(std::bind(&Button::onLeave, this, std::placeholders::_1));
    m_mouseInteraction.addOnLeftClickEvent(std::bind(&Button::onLeftClick, this, std::placeholders::_1));
  }

  //------------------------------------------------------------------------------------------------
  void Button::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    m_clickTimer += secondsPerUpdate;
    
    if (m_state == kClicked && m_clickTimer > s_maxTime)
    {
      if (m_collider.intersectsPoint(GameManager::getInputManager()->getMouse()->getMousePosition()))
      {
        m_spriteRenderer.setTexture("ButtonHighlighted.png");
        m_state = kHighlighted;
      }
      else
      {
        m_spriteRenderer.setTexture("ButtonDefault.png");
        m_state = kIdle;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Button::onEnter(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture("ButtonHighlighted.png");
    m_state = kHighlighted;
  }

  //------------------------------------------------------------------------------------------------
  void Button::onLeave(Handle<GameObject> sender)
  {
    m_spriteRenderer.setTexture("ButtonDefault.png");
  }

  //------------------------------------------------------------------------------------------------
  void Button::onLeftClick(Handle<GameObject> sender)
  {
    if (m_state != kClicked)
    {
      m_spriteRenderer.setTexture("ButtonPressed.png");
      m_state = kClicked;
      m_clickTimer = 0;
    }
  }
}
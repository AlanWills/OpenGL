#include "stdafx.h"

#include "UI/Button.h"


namespace OpenGL
{
  REGISTER_COMPONENT(Button)

  //------------------------------------------------------------------------------------------------
  Button::Button()
  {
    ADD_CLASS_COMPONENT(RectangleCollider, m_collider);
    ADD_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer);
    ADD_CLASS_COMPONENT(TextRenderer, m_textRenderer);
  }

  //------------------------------------------------------------------------------------------------
  Button::~Button()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Button::initialize()
  {
    Inherited::initialize();

    m_spriteRenderer.setTransform(&m_transform);
    m_spriteRenderer.setTexture("ButtonDefault");

    m_collider.setTransform(&m_transform);
    m_collider.setDimensions(m_spriteRenderer.getDimensions());
  }
}
#pragma once

#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "Input/MouseInteractionHandler.h"
#include "UI/Label.h"


namespace OpenGL
{

class Button : public GameObject
{
  enum ButtonState
  {
    kIdle,
    kHighlighted,
    kClicked,
  };

  public:
    Button();
    virtual ~Button();

    void initialize(Handle<Component> allocHandle) override;
    void update(GLfloat secondsPerUpdate) override;

    /// \brief Subscribes a callback to the onLeftClick event in the MouseInteractionHandler component on this object
    void addOnLeftClickEvent(const GameObjectClickCallback& onLeftClick) { m_mouseInteraction.addOnLeftClickEvent(onLeftClick); }

  private:
    typedef GameObject Inherited;

    void onEnter(Handle<GameObject> sender);
    void onLeave(Handle<GameObject> sender);
    void onLeftClick(Handle<GameObject> sender);

    DECLARE_CLASS_COMPONENT(RectangleCollider, m_collider)
    DECLARE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer)
    DECLARE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction)
    DECLARE_CLASS_COMPONENT(Label, m_label);

    static const float s_maxTime;
    float m_clickTimer;
    ButtonState m_state;
};

}
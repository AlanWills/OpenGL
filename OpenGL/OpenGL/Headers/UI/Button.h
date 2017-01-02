#pragma once

#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/SpriteRenderer.h"
#include "Rendering/TextRenderer.h"
#include "Input/MouseInteractionHandler.h"


namespace OpenGL
{

class Button : public GameObject
{
  public:
    Button();
    virtual ~Button();

    void initialize(Handle<Component> allocHandle) override;

  private:
    void onEnter(Handle<GameObject> sender);
    void onLeave(Handle<GameObject> sender);

    typedef GameObject Inherited;

    DECLARE_CLASS_COMPONENT(RectangleCollider, m_collider)
    DECLARE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer)
    DECLARE_CLASS_COMPONENT(TextRenderer, m_textRenderer)
    DECLARE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction)
};

}
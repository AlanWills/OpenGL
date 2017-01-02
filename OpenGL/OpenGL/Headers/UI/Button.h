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
    void handleInput(GLfloat elapsedGameTime) override;

    void test(Handle<GameObject>);

  private:
    typedef GameObject Inherited;

    DECLARE_CLASS_COMPONENT(RectangleCollider, m_collider)
    DECLARE_CLASS_COMPONENT(SpriteRenderer, m_spriteRenderer)
    DECLARE_CLASS_COMPONENT(TextRenderer, m_textRenderer)
    DECLARE_CLASS_COMPONENT(MouseInteractionHandler, m_mouseInteraction)
};

}
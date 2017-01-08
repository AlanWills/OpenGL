#pragma once

#include "Objects/GameObject.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{

class Label : public GameObject
{
  public:
    Label();
    virtual ~Label();

    void initialize(Handle<Component> allocHandle) override;
    void render(GLfloat lag) override;

  private:
    typedef GameObject Inherited;

    DECLARE_CLASS_COMPONENT(TextRenderer, m_textRenderer)
};

}
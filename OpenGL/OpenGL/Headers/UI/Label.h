#pragma once

#include "Objects/UIObject.h"
#include "Rendering/TextRenderer.h"


namespace OpenGL
{

class Label : public UIObject
{
  public:
    Label();
    virtual ~Label();

    void initialize(Handle<Component> allocHandle) override;
    void render(GLfloat lag) override;

  private:
    typedef UIObject Inherited;

    DECLARE_CLASS_COMPONENT(TextRenderer, m_textRenderer)
};

}
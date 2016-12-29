#pragma once

#include "Objects/Component.h"


namespace OpenGL
{

class Collider : public Component
{
  public:
    Collider();
    ~Collider();

    void handleInput(GLfloat elapsedGameTime) override;

  private:
    typedef Component Inherited;

    bool m_mouseOver;
    bool m_clicked;
    bool m_pressed;
};

}
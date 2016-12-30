#pragma once

#include "Objects/Component.h"
#include "Maths/Ray.h"


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
    
    virtual bool intersectsRay(const Ray& ray) = 0;

    bool m_mouseOver;
    bool m_clicked;
    bool m_pressed;
};

}
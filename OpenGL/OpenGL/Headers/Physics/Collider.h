#pragma once

#include "Objects/Component.h"
#include "Maths/Ray.h"
#include "Maths/Transform.h"


namespace OpenGL
{

  class Collider : public Component
  {
  public:
    Collider();
    virtual ~Collider();

    void awake() override;
    void handleInput(GLfloat elapsedGameTime) override;

    void setTransform(Transform* transform) { m_transform = transform; }

    bool isMouseOver() const { return m_mouseOver; }
    bool isClicked() const { return m_clicked; }
    bool isPressed() const { return m_pressed; }

  protected:
    typedef Component Inherited;
    
    virtual bool intersectsRay(const Ray& ray) = 0;

    bool m_mouseOver;
    bool m_clicked;
    bool m_pressed;

    Transform* m_transform;
};

}
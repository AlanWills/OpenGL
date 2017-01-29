#pragma once

#include "Objects/Component.h"
#include "Maths/Ray.h"
#include "Maths/Transform.h"
#include "Maths/Rectangle.h"


namespace OpenGL
{

  class Collider : public Component
  {
  public:
    Collider();
    virtual ~Collider();

    void awake() override;

    virtual bool intersects(const Ray& ray) const = 0;
    virtual bool intersects(const glm::vec2& point) const = 0;
    virtual bool intersects(const Rectangle& collider) const = 0;

  protected:
    typedef Component Inherited;

    Handle<Transform> m_transform;
};

}
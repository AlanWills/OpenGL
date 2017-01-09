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

    virtual bool intersectsRay(const Ray& ray) const = 0;
    virtual bool intersectsPoint(const glm::vec2& point) const = 0;

  protected:
    typedef Component Inherited;

    Handle<Transform> m_transform;
};

}
#pragma once

#include "Objects/Component.h"


namespace OpenGL
{
  
class RigidBody2D : public Component
{
  DECLARE_COMPONENT_WITH_MANAGER(PoolAllocator, RigidBody2D, 100, PhysicsManager);

  public:
    void update(GLfloat secondsPerUpdate) override;

    void setLinearVelocity(const glm::vec2& linearVelocity) { m_linearVelocity = linearVelocity; }

    /// \brief Positive is clockwise
    void setAngularVelocity(float angularVelocity) { m_angularVelocity = angularVelocity; }

  private:
    typedef Component Inherited;

    glm::vec2 m_linearVelocity;

    float m_angularVelocity;
};

}
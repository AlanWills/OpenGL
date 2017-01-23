#include "stdafx.h"

#include "Physics/RigidBody2D.h"
#include "Objects/GameObject.h"


namespace OpenGL
{
  REGISTER_COMPONENT(RigidBody2D);

  //------------------------------------------------------------------------------------------------
  RigidBody2D::RigidBody2D() :
    m_linearVelocity(0, 0),
    m_angularVelocity(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  RigidBody2D::~RigidBody2D()
  {
  }

  //------------------------------------------------------------------------------------------------
  void RigidBody2D::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    const Handle<Transform>& transform = getParent()->getTransform();

    if (m_linearVelocity != glm::zero<glm::vec2>())
    {
      transform->translate(glm::vec3(m_linearVelocity * secondsPerUpdate, 0));
    }

    if (m_angularVelocity != 0)
    {
      const glm::mat4& matrix = glm::rotate(glm::mat4(), m_angularVelocity * secondsPerUpdate, glm::vec3(0, 0, 1));
      transform->applyTransform(matrix);
    }
  }
}
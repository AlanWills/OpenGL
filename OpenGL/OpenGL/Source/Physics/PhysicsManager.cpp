#include "stdafx.h"

#include "Physics/PhysicsManager.h"
#include "Physics/RigidBody2D.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  void PhysicsManager::awake()
  {
    Inherited::awake();

    RigidBody2D::m_componentAllocator.awake();
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);

    RigidBody2D::m_componentAllocator.handleInput(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    RigidBody2D::m_componentAllocator.update(secondsPerUpdate);
  }

  //------------------------------------------------------------------------------------------------
  void PhysicsManager::render(GLfloat lag)
  {
    Inherited::render(lag);

    RigidBody2D::m_componentAllocator.render(lag);
  }
}
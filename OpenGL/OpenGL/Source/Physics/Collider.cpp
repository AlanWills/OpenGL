#include "stdafx.h"

#include "Physics/Collider.h"
#include "Objects/GameObject.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Collider::Collider()
  {
  }

  //------------------------------------------------------------------------------------------------
  Collider::~Collider()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Collider::awake()
  {
    Inherited::awake();

    ASSERT(getParent().get());
    m_transform = &getParent()->getTransform();
  }
}
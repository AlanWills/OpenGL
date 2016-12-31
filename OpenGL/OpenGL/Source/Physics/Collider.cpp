#include "stdafx.h"

#include "Physics/Collider.h"


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

    ASSERT(m_transform);
  }
}
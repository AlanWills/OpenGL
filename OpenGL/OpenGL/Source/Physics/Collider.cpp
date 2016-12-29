#include "stdafx.h"

#include "Physics/Collider.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  Collider::Collider() :
    m_mouseOver(false),
    m_clicked(false),
    m_pressed(false)
  {
  }

  //------------------------------------------------------------------------------------------------
  Collider::~Collider()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Collider::handleInput(GLfloat elapsedGameTime)
  {
    Inherited::handleInput(elapsedGameTime);


  }
}
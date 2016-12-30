#include "stdafx.h"

#include "Physics/Collider.h"
#include "Game/GameManager.h"


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

    Camera* camera = GameManager::getScreenManager()->getViewport()->getCamera();
    Mouse* mouse = GameManager::getInputManager()->getMouse();

    m_mouseOver = intersectsRay(camera->createRay(mouse->getMousePosition()));
  }
}
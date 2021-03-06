#include "stdafx.h"

#include "Turrets/Turret.h"
#include "Animation/StateMachine.h"
#include "Screens/Screen.h"
#include "Objects/GameObject.h"
#include "Physics/RigidBody2D.h"

using namespace CelesteEngine::Physics;


namespace SpaceGame
{
  REGISTER_SCRIPT(Turret, 10)

  //------------------------------------------------------------------------------------------------
  Turret::Turret() :
    m_currentFireTimer(0)
  {
  }

  //------------------------------------------------------------------------------------------------
  Turret::~Turret()
  {
  }

  //------------------------------------------------------------------------------------------------
  void Turret::onUpdate(GLfloat elapsedGameTime)
  {
    Inherited::onUpdate(elapsedGameTime);

    m_currentFireTimer += elapsedGameTime;
    if (m_currentFireTimer > 1)
    {
      m_currentFireTimer = 0;
      fire();
    }
  }

  //------------------------------------------------------------------------------------------------
  void Turret::onDeath()
  {
    Inherited::onDeath();

    m_currentFireTimer = 0;
  }

  //------------------------------------------------------------------------------------------------
  void Turret::fire()
  {
    // Do not parent bullet to ship transform!
    const Handle<GameObject>& bullet = getGameObject()->allocateGameObjectInSameLayer();
    bullet->getTransform()->setWorldTranslation(getTransform()->getWorldTranslation());
    bullet->getTransform()->setWorldRotation(getTransform()->getWorldRotation());

    SpriteRenderer::create(bullet, "GreenLaserRay.png");
    RigidBody2D::create(bullet, glm::vec2(getTransform()->getWorldMatrix()[1]) * 500.0f, 0);
  }

  //------------------------------------------------------------------------------------------------
  void Turret::create(const Handle<GameObject>& turret)
  {
    const Handle<StateMachine>& turretStateMachine = turret->addComponent<StateMachine>();
    const Handle<Animation>& idleAnimation = turret->addComponent<Animation>();
  }
}
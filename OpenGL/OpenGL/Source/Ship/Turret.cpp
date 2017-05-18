#include "stdafx.h"

#include "Ship/Turret.h"
#include "Animation/StateMachine.h"


namespace SpaceGame
{
  //------------------------------------------------------------------------------------------------
  void Turret::create(const Handle<GameObject>& turret)
  {
    const Handle<StateMachine>& turretStateMachine = turret->addComponent<StateMachine>();
    const Handle<Animation>& idleAnimation = turret->addComponent<Animation>();
  }
}
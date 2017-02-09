#include "stdafx.h"

#include "Factories/SpaceScreenFactory.h"
#include "Levels/SpaceLevel.h"


namespace Space
{
  //------------------------------------------------------------------------------------------------
  void transitionToGameplayScreen(const Handle<Screen>& screen, const std::string& relativeLevelDataFilePath)
  {
      SpaceLevel::load(screen, relativeLevelDataFilePath);

      /*Handle<GameObject> turret = screen->allocateAndInitializeGameObject();
      {
        const Handle<RigidBody2D>& rigidBody2D = turret->addComponent<kManaged>(RigidBody2D::allocateAndInitialize());
        rigidBody2D->setAngularVelocity(0.1f);

        const Handle<SpriteRenderer>& renderer = turret->addComponent<kManaged>(SpriteRenderer::allocateAndInitialize());
        const Handle<StateMachine>& stateMachine = turret->addComponent<kUnmanaged>(StateMachine::allocateAndInitialize());

        const Handle<Animation>& idleAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
        idleAnimation->addFrame("ChainBlasterFrame0.png");
        idleAnimation->setSecondsPerFrame(0.1f);
        idleAnimation->setLoop(false);

        const Handle<Animation>& firingAnimation = turret->addComponent<kUnmanaged>(Animation::allocateAndInitialize());
        idleAnimation->addFrame("ChainBlasterFrame0.png");
        firingAnimation->addFrame("ChainBlasterFrame1.png");
        firingAnimation->addFrame("ChainBlasterFrame2.png");

        const Handle<AnimationState>& idleState = stateMachine->addState(idleAnimation);
        const Handle<AnimationState>& firingState = stateMachine->addState(firingAnimation);
        stateMachine->setStartingState(idleState);
        idleState->addTransition(firingState, std::bind(&ScreenFactory::firing, *this));
        firingState->addTransition(idleState, std::bind(&ScreenFactory::notFiring, *this));
      }*/
  }
}
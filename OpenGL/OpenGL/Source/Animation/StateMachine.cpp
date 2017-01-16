#include "stdafx.h"

#include "Animation/StateMachine.h"


namespace OpenGL
{
  REGISTER_COMPONENT(StateMachine);

  //------------------------------------------------------------------------------------------------
  StateMachine::StateMachine() :
    m_currentAnimState(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  StateMachine::~StateMachine()
  {
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::update(GLfloat secondsPerUpdate)
  {
    Inherited::update(secondsPerUpdate);

    ASSERT(m_currentAnimState.get());

    for (const Handle<Transition>& transition : *m_currentAnimState)
    {
      // The first check is due to this current implementation - we normally wouldn't need to test transition to current animstate
      if (transition->testTransitionFunction())
      {
        // Stop this current animation from playing and reset it back to it's beginning
        m_currentAnimState->stopAnimation();

        // Now update the current animation state to the destination state of the transition and play it
        m_currentAnimState = m_states[1];
        m_currentAnimState->startAnimation();

        // Currently we transition on the first one that passes
        break;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  Handle<AnimationState> StateMachine::addState(const Handle<Animation>& animation)
  {
    if (!m_stateAllocator.canAllocate())
    {
      ASSERT_FAIL("Run out of states.  Consider increasing the pool size");
    }

    // Set up the animation state properties
    Handle<AnimationState> animState = m_stateAllocator.allocate();
    animState->setAnimation(animation);

    m_states.push_back(animState);

    return animState;
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::setStartingState(const Handle<AnimationState>& animState)
  {
    ASSERT(!isAwake());
    ASSERT(animState.get());
    m_currentAnimState = animState;
  }
}
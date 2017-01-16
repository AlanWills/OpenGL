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

    // Need to abstractify this - have animation states which themselves contain the transitions
    // And then simply check all the transitions going from that state
    // This sucks
    for (const Handle<Transition>& transition : m_transitions)
    {
      // The first check is due to this current implementation - we normally wouldn't need to test transition to current animstate
      if (transition->getDestinationState() != m_currentAnimState &&
          transition->testTransitionFunction())
      {
        ASSERT(m_currentAnimState.get());

        // Stop this current animation from playing and reset it back to it's beginning
        m_currentAnimState->pause();
        m_currentAnimState->restart();

        // Now update the current animation state to the destination state of the transition and play it
        m_currentAnimState = transition->getDestinationState();
        m_currentAnimState->restart();    // This resets the sprite renderer's texture for the parent
        m_currentAnimState->resume();

        // Currently we transition on the first one that passes
        break;
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  const Handle<Transition>& StateMachine::addTransition(
    const Handle<Animation>& from,
    const Handle<Animation>& to,
    const Transition::TransitionFunc& transitionFunc)
  {
    if (!m_transitionAllocator.canAllocate())
    {
      ASSERT_FAIL("Run out of transitions.  Consider increasing the pool size");
    }

    // Cannot have a self transition
    ASSERT(from != to);

    // Set up the transition properties
    Handle<Transition> transition = m_transitionAllocator.allocate();
    transition->setSourceState(from);
    transition->setDestinationState(to);
    transition->setTransitionFunction(transitionFunc);

    m_transitions.push_back(transition);

    return transition;
  }

  //------------------------------------------------------------------------------------------------
  void StateMachine::setStartingAnimState(const Handle<Animation>& animState)
  {
    ASSERT(!isAwake());
    ASSERT(animState.get());
    m_currentAnimState = animState;
  }
}
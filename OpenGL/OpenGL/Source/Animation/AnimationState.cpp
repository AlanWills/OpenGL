#include "stdafx.h"

#include "Animation/AnimationState.h"


namespace OpenGL
{
  //------------------------------------------------------------------------------------------------
  AnimationState::AnimationState() :
    m_animation(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  AnimationState::~AnimationState()
  {
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::awake()
  {
    Inherited::awake();

    ASSERT(m_animation.get());
  }

  //------------------------------------------------------------------------------------------------
  Handle<Transition> AnimationState::addTransition(
    const Handle<AnimationState>& to,
    const Transition::TransitionFunc& transitionFunc)
  {
    if (!m_transitionAllocator.canAllocate())
    {
      ASSERT_FAIL("Run out of transitions.  Consider increasing the pool size");
    }

    // Cannot have a self transition
    ASSERT(getAllocatorHandle() != to);

    // Set up the transition properties
    Handle<Transition> transition = m_transitionAllocator.allocate();
    transition->setDestinationState("This isn't going to work");
    transition->setTransitionFunction(transitionFunc);

    m_transitions.push_back(transition);

    return transition;
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::setAnimation(const Handle<Animation>& animation)
  {
    if (m_animation.get())
    {
      m_animation->die();
    }

    m_animation = animation;
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::startAnimation()
  {
    // This resets the sprite renderer's texture for the parent
    m_animation->restart();
    m_animation->resume();
  }

  //------------------------------------------------------------------------------------------------
  void AnimationState::stopAnimation()
  {
    m_animation->pause();
    m_animation->restart();
  }
}
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
  void AnimationState::addTransition(
    const Handle<AnimationState>& to,
    const TransitionFunc& transitionFunc)
  {
    // Cannot have a self transition
    ASSERT(getAllocatorHandle() != to);

    // Add the transition to the map
    m_transitions.emplace(to, transitionFunc);
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